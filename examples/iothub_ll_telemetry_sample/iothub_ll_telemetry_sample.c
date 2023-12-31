#include <stdio.h>
#include <stdlib.h>
#include "dht.h"
#include "hardware/adc.h"
#include "iothub.h"
#include "iothub_device_client_ll.h"
#include "iothub_client_options.h"
#include "iothub_message.h"
#include "iothub_client_version.h"
#include "azure_c_shared_utility/threadapi.h"
#include "azure_c_shared_utility/tickcounter.h"
#include "azure_c_shared_utility/crt_abstractions.h"
#include "azure_c_shared_utility/shared_util_options.h"
#include "azure_c_shared_utility/agenttime.h"
#include "azure_c_shared_utility/http_proxy_io.h"
#include "azure_prov_client/prov_device_ll_client.h"
#include "azure_prov_client/prov_security_factory.h"

#include "azure_samples.h"

/* This sample uses the _LL APIs of iothub_client for example purposes.
Simply changing the using the convenience layer (functions not having _LL)
and removing calls to _DoWork will yield the same results. */

// The protocol you wish to use should be uncommented
//
#define SAMPLE_MQTT
//#define SAMPLE_MQTT_OVER_WEBSOCKETS
//#define SAMPLE_AMQP
//#define SAMPLE_AMQP_OVER_WEBSOCKETS
//#define SAMPLE_HTTP

#define ANALOG_PIN 26




#ifdef SAMPLE_MQTT
#include "iothubtransportmqtt.h"
#endif // SAMPLE_MQTT
#ifdef SAMPLE_MQTT_OVER_WEBSOCKETS
#include "iothubtransportmqtt_websockets.h"
#endif // SAMPLE_MQTT_OVER_WEBSOCKETS
#ifdef SAMPLE_AMQP
#include "iothubtransportamqp.h"
#endif // SAMPLE_AMQP
#ifdef SAMPLE_AMQP_OVER_WEBSOCKETS
#include "iothubtransportamqp_websockets.h"
#endif // SAMPLE_AMQP_OVER_WEBSOCKETS
#ifdef SAMPLE_HTTP
#include "iothubtransporthttp.h"
#endif // SAMPLE_HTTP

#ifdef SET_TRUSTED_CERT_IN_SAMPLES
#include "certs.h"
#endif // SET_TRUSTED_CERT_IN_SAMPLES

/* Paste in the your iothub connection string  */
//static const char* connectionString = "[device connection string]";
static const char *connectionString = pico_az_connectionString;

#define MESSAGE_COUNT 3000 //defines how many messages will be sent
static bool g_continueRunning = true;
static size_t g_message_count_send_confirmations = 0;
static size_t g_message_recv_count = 0;

static void send_confirm_callback(IOTHUB_CLIENT_CONFIRMATION_RESULT result, void *userContextCallback)
{
    (void)userContextCallback;
    // When a message is sent this callback will get envoked
    g_message_count_send_confirmations++;
    (void)printf("Confirmation callback received for message %lu with result %s\r\n", (unsigned long)g_message_count_send_confirmations, MU_ENUM_TO_STRING(IOTHUB_CLIENT_CONFIRMATION_RESULT, result));
}

static void connection_status_callback(IOTHUB_CLIENT_CONNECTION_STATUS result, IOTHUB_CLIENT_CONNECTION_STATUS_REASON reason, void *user_context)
{
    (void)reason;
    (void)user_context;
    // This sample DOES NOT take into consideration network outages.
    if (result == IOTHUB_CLIENT_CONNECTION_AUTHENTICATED)
    {
        (void)printf("The device client is connected to iothub\r\n");
    }
    else
    {
        (void)printf("The device client has been disconnected\r\n");
        g_continueRunning = false;
    }
}

//// DHT

// change this to match your setup
//static const dht_model_t DHT_MODEL = DHT11;
//static const uint DATA_PIN = 27;

/*static float celsius_to_fahrenheit(float temperature) {
    return temperature * (9.0f / 5) + 32;
}
*/
/// --DHT






void iothub_ll_telemetry_sample(void)
{
    IOTHUB_CLIENT_TRANSPORT_PROVIDER protocol;
    size_t messages_count = 0; //was 10 before
    IOTHUB_MESSAGE_HANDLE message_handle;
    size_t messages_sent = 0;

    //float telemetry_temperature;
    //float telemetry_humidity;
    float voltage;
    float pressure;
    uint16_t analogValue;
    adc_init();
    adc_select_input(0); // Use channel 0 for GPIO 26
    //const char *telemetry_scale = "Celsius";
    char telemetry_msg_buffer[80];

    // Select the Protocol to use with the connection
#ifdef SAMPLE_MQTT
    protocol = MQTT_Protocol;
#endif // SAMPLE_MQTT
#ifdef SAMPLE_MQTT_OVER_WEBSOCKETS
    protocol = MQTT_WebSocket_Protocol;
#endif // SAMPLE_MQTT_OVER_WEBSOCKETS
#ifdef SAMPLE_AMQP
    protocol = AMQP_Protocol;
#endif // SAMPLE_AMQP
#ifdef SAMPLE_AMQP_OVER_WEBSOCKETS
    protocol = AMQP_Protocol_over_WebSocketsTls;
#endif // SAMPLE_AMQP_OVER_WEBSOCKETS
#ifdef SAMPLE_HTTP
    protocol = HTTP_Protocol;
#endif // SAMPLE_HTTP

    // Used to initialize IoTHub SDK subsystem
    (void)IoTHub_Init();
    IOTHUB_DEVICE_CLIENT_LL_HANDLE device_ll_handle;

    (void)printf("Creating IoTHub Device handle\r\n");
    // Create the iothub handle here
    device_ll_handle = IoTHubDeviceClient_LL_CreateFromConnectionString(connectionString, protocol);
    if (device_ll_handle == NULL)
    {
        (void)printf("Failure creating IotHub device. Hint: Check your connection string.\r\n");
    }
    else
    {
        // Set any option that are neccessary.
        // For available options please see the iothub_sdk_options.md documentation
#ifndef SAMPLE_HTTP
        // Can not set this options in HTTP
        bool traceOn = true;
        IoTHubDeviceClient_LL_SetOption(device_ll_handle, OPTION_LOG_TRACE, &traceOn);
#endif

#ifdef SET_TRUSTED_CERT_IN_SAMPLES
        // Setting the Trusted Certificate. This is only necessary on systems without
        // built in certificate stores.
        //(void)printf("IoTHubDeviceClient_LL_SetOption, %s\r\n", certificates);
        IoTHubDeviceClient_LL_SetOption(device_ll_handle, OPTION_TRUSTED_CERT, certificates);
#endif // SET_TRUSTED_CERT_IN_SAMPLES

#if defined SAMPLE_MQTT || defined SAMPLE_MQTT_OVER_WEBSOCKETS
        // Setting the auto URL Encoder (recommended for MQTT). Please use this option unless
        // you are URL Encoding inputs yourself.
        // ONLY valid for use with MQTT
        bool urlEncodeOn = true;
        OPTION_KEEP_ALIVE = "1000000";

        (void)IoTHubDeviceClient_LL_SetOption(device_ll_handle, OPTION_KEEP_ALIVE, &urlEncodeOn);
        //(void)IoTHubDeviceClient_LL_SetOption(device_ll_handle, OPTION_AUTO_URL_ENCODE_DECODE, &urlEncodeOn);
#endif
        // Setting connection status callback to get indication of connection to iothub
        (void)IoTHubDeviceClient_LL_SetConnectionStatusCallback(device_ll_handle, connection_status_callback, NULL);

        //sleep_ms(5000);

// DHT //////////////////////

    //stdio_init_all();
    //adc_init();
    //adc_set_temp_sensor_enabled(false);
    //adc_select_input(ANALOG_PIN);
    //dht_t dht;
    //dht_init(&dht, DHT_MODEL, pio0, DATA_PIN, true /* pull_up */);


////////////////

// ADC 

        do
        
        {
            if (messages_sent < MESSAGE_COUNT)
            {
                char telemetry_msg_buffer[80];
                adc_select_input(0); // Use channel 0 for GPIO 26
                analogValue = adc_read();  // Read the raw 12-bit ADC value
                printf("Analog Value: %d\n", analogValue);
                
                voltage = analogValue * (4.5f / (1 << 12));  // Convert to voltage (assuming Vref = 4.5V; from datasheet TIZLA60)
                pressure =  voltage * 1.33 - 0.7; //(6Bar/4.5V -0.7V)

                printf("Voltage: %.2fV\n", voltage);
                printf("pressure: %.2fbar\n", pressure);
                //sleep_ms(1000);

                 // Construct the iothub message
                //telemetry_temperature = 20.0f;
                //telemetry_humidity = 60.0f;

                //// DHT
/*
                dht_start_measurement(&dht);
        
                float humidity;
                float temperature_c;
                dht_result_t result = dht_finish_measurement_blocking(&dht, &humidity, &temperature_c);
                if (result == DHT_RESULT_OK) {
                    telemetry_temperature = (temperature_c);
                    telemetry_humidity = humidity;  
                } else if (result == DHT_RESULT_TIMEOUT) {
                puts("DHT sensor not responding. Please check your wiring.");
                } else {
                assert(result == DHT_RESULT_BAD_CHECKSUM);
                puts("Bad checksum");
                }
        

                sprintf(telemetry_msg_buffer, "{\"temperature\":%.3f,\"humidity\":%.3f,\"scale\":\"%s\"}",
                       telemetry_temperature, telemetry_humidity, telemetry_scale);

*/
                //char SensorID[] = "00008DC6D7442"; //MAC address of the WifFI360-EVB-Pico
                //sprintf(telemetry_msg_buffer, "{\"SensorID\":%s,\"pressure\":%.3f}",SensorID, pressure);
                //float SensorIDfloat = 1.0;
                //sprintf(telemetry_msg_buffer, "{\"SensorID\":%.3f,\"pressure\":%.3f}",pressure, pressure);
                sprintf(telemetry_msg_buffer, "{\"pressure\":%.3f}", pressure);

                message_handle = IoTHubMessage_CreateFromString(telemetry_msg_buffer);

                // Set Message property
                (void)IoTHubMessage_SetMessageId(message_handle, "MSG_ID");
                (void)IoTHubMessage_SetCorrelationId(message_handle, "CORE_ID");
                (void)IoTHubMessage_SetContentTypeSystemProperty(message_handle, "application%2fjson");
                (void)IoTHubMessage_SetContentEncodingSystemProperty(message_handle, "utf-8");

                // Add custom properties to message
                //(void)IoTHubMessage_SetProperty(message_handle, "property_key", "property_value");
                // dont use blank, special char. need encoding
                (void)IoTHubMessage_SetProperty(message_handle, "FirmwareID", "00008DC6D7442");
               

                //(void)printf("Sending message %d to IoTHub\r\n", (int)(messages_sent + 1));
                //IoTHubDeviceClient_LL_SendEventAsync(device_ll_handle, message_handle, send_confirm_callback, NULL);
                (void)printf("\r\nSending message %d to IoTHub\r\nMessage: %s\r\n", (int)(messages_sent + 1), telemetry_msg_buffer);
                //IoTHubDeviceClient_SendEventAsync(device_handle, message_handle, send_confirm_callback, NULL);
                IoTHubDeviceClient_LL_SendEventAsync(device_ll_handle, message_handle, send_confirm_callback, NULL);

                // The message is copied to the sdk so the we can destroy it
                IoTHubMessage_Destroy(message_handle);

                messages_sent++;


 
            }
            else if (g_message_count_send_confirmations >= MESSAGE_COUNT)
            {
                // After all messages are all received stop running
                g_continueRunning = false;            

            }

            IoTHubDeviceClient_LL_DoWork(device_ll_handle);
            ThreadAPI_Sleep(10);
            printf("After ThreadAPI_Sleep\n");
            printf("%d\n", g_continueRunning);

            sleep_ms(10); // wait for

        } while (g_continueRunning);

        // Clean up the iothub sdk handle
        IoTHubDeviceClient_LL_Destroy(device_ll_handle);
    }
    // Free all the sdk subsystem
    IoTHub_Deinit();
}
