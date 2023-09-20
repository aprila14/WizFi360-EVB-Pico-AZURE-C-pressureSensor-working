/**
 * Copyright (c) 2022 WIZnet Co.,Ltd
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "azure_samples.h"


const char pico_az_connectionString[] = "";


const char pico_az_x509connectionString[] = "HostName=pressure-sensor-IoT-hub.azure-devices.net;DeviceId=sparkhub-pressure-sensor1-x509casigned;x509=true";

const char pico_az_x509certificate[] =
"-----BEGIN CERTIFICATE-----""\n"
"MIIDdDCCAlygAwIBAgIQFiSFPcSv85PIRj35A4kFKzANBgkqhkiG9w0BAQsFADAT\n"
"MREwDwYDVQQDDAhzcGFya2h1YjAeFw0yMzA5MTcxNjA5MjNaFw0zMzA5MTQxNjA5\n"
"MjNaMGIxCzAJBgNVBAYTAkNIMQ8wDQYDVQQIDAZadXJpY2gxETAPBgNVBAoMCHNw\n"
"YXJraHViMS8wLQYDVQQDDCZzcGFya2h1Yi1wcmVzc3VyZS1zZW5zb3IxLXg1MDlj\n"
"YXNpZ25lZDCCASIwDQYJKoZIhvcNAQEBBQADggEPADCCAQoCggEBAMpRp+7Ho49l\n"
"gpEUVBdUyErsijAWgx/8z115MNwJEpsPtHnZRTZRmDvZN1fy5eGFcoE4fjdX0peQ\n"
"C3xfvekEbUd6nnlFw3tppf+NMst/iT8fSwk6JfoHabCKOtpaJlGPnIOMVL7vwQ4J\n"
"TaWFJE9OmXwTZhgAWGsa7JQIwHgtYiHEidpMJI4nQC3R6Jr8uRWwy7li62NmhA27\n"
"adaBNXFlTqmlCFL7wxKYm1Jx7+wx2PmBg3iApTKL7ILhLhP5+yGYlHBLRJQy6iGp\n"
"XYMa1HdeO35b3ZvCNXiUUHxbB1YbnN00lmgVSdfsl/q+Y3K/ugfeJg08yXoGgflH\n"
"XU990Mk3vnECAwEAAaN1MHMwHwYDVR0jBBgwFoAUJbQ7Umg1bHofPHzZFuT1hUic\n"
"xZQwDAYDVR0TAQH/BAIwADATBgNVHSUEDDAKBggrBgEFBQcDAjAOBgNVHQ8BAf8E\n"
"BAMCB4AwHQYDVR0OBBYEFB85tRfQoAojmHrvv9U6UCwYZOreMA0GCSqGSIb3DQEB\n"
"CwUAA4IBAQA0oc32KHygli2aKUVx1/4WBSOw72X8A1nlR0ZYRU6gV2sW2IMcNTg3\n"
"ncNPyu9IRfhGHBAAzcsEvHMS93FGFdntUS6RgTp+NJwO5tCgDOY0vJ0cP53XzGU+\n"
"niTO8RkU0HrKUCpEa9ZTLGA9GkhV6vliMkj0BhWkZwmTctx26H1x+CazalKnYKOG\n"
"czmlUlf38YcsN4Fw0oYW9wPsLUXv3bMrvRyg8JU+Z8DAvw4IG4O9vJe3yg5MHLKR\n"
"XeAl0njLF4RgL1ejoGjXPj9yjlbSu6cgc5cLR/cIU22IuwZSI+f4MKtatgVU2xFq\n"
"SHnJ1g8Bw1EtQLc4+nrVY9g3S6/43qyk\n"
"-----END CERTIFICATE-----";

const char pico_az_x509privatekey[] =
"-----BEGIN PRIVATE KEY-----""\n"
"MIIEuwIBADANBgkqhkiG9w0BAQEFAASCBKUwggShAgEAAoIBAQDKUafux6OPZYKR\n"
"FFQXVMhK7IowFoMf/M9deTDcCRKbD7R52UU2UZg72TdX8uXhhXKBOH43V9KXkAt8\n"
"X73pBG1Hep55RcN7aaX/jTLLf4k/H0sJOiX6B2mwijraWiZRj5yDjFS+78EOCU2l\n"
"hSRPTpl8E2YYAFhrGuyUCMB4LWIhxInaTCSOJ0At0eia/LkVsMu5YutjZoQNu2nW\n"
"gTVxZU6ppQhS+8MSmJtSce/sMdj5gYN4gKUyi+yC4S4T+fshmJRwS0SUMuohqV2D\n"
"GtR3Xjt+W92bwjV4lFB8WwdWG5zdNJZoFUnX7Jf6vmNyv7oH3iYNPMl6BoH5R11P\n"
"fdDJN75xAgMBAAECgf9DhVz2Y8pCYS5iHNazsqfl2WuFAP5h/o12NKwJwz1iYqto\n"
"vwpKRpD36FaAE6CE03STi7cT4Ut3KaurpohK7B9Ma6/X6WCEH44263i4UagMWPVB\n"
"7xYdi7vKH1fk55FCRxuFC6B82KcleBVh2D11+lVfA1pfSD46AJJUFVemw/6sJcOi\n"
"v6MMvsaeAxrwl7v3D6cz5SbbnD0cmlx6eBgB3u1OfjTxhKsz15KLS9ERy23WxjFR\n"
"Je6eqCiNUJsalSAWIm/qPQobns1UleIOvnfYuhZvkY5g1OZRuDl7E+c4Iqg44qwB\n"
"O7DbSEw3FWqbODEjousxNtaO15gVkCJEh2927qECgYEA3Os0xdDW48rdXaOMQC67\n"
"KVmis9xx+cy2j/zrvUyg8/Sf+WxOVo8x8i2hM2uOlBeYAt3l6O4eSsizqgmlV76s\n"
"TNGOPe8Cd47uPpfynqgltGlDVs6h+Buc1egZop1CNODSGVSDm5p4eGsOtk1NFEyW\n"
"GU1ybr9mU/6dC6q/5Bb84hECgYEA6nJUijqTvT5S0qXx6sb8xVos5U5c73bdmt7G\n"
"IYHybsZ9DxdxWR/ta99bXBXvHkddtASD5Bo2fVUhnoB/BiJI6IZtwmCLK17Rs+61\n"
"heCdShsupgwysiSddRwOzaPyTyGGMz7tC2tqTCOcjg1Bz+qdFbCZAtUNdwxcIpV1\n"
"l1HOtmECgYBXLaInpeAHCFkOyKlh8o79JFgmbgm0L+qjK4XDr+ecHZ67iNfpJJzr\n"
"GsKQThN3sU/VYceGgeEGVelAYooS9DV+IvvkyNrKX2b44HFn1qb6aMegC+6ywALG\n"
"Ds9+8lvcDhQa1tUQpIaBzo2Bt0OBjS92UK+lsHYrE0DaB8mtsrycYQKBgQDJECY6\n"
"qgP8P4/uQg0YCXHMmwp32d3QLMPexwFqyTQuFqI4KCW4hq4qXlLOxazd7dyJv3mR\n"
"TX2/vRvpAFBv5UVbzbYiBoQ0PMxhoO4ik8CxRmCaXUm5B7fWMKrtZ5YukRSzrFrE\n"
"+WkfRUdFeE8hzhbL/DkteaRjncECk+VWUf2S4QKBgCzxZDf+bh2CJIa/lysrXlnx\n"
"zcOHXLoGMj/RMtQAdKLTTC01wEUaPJ9Flj6IqUhF+CqTnr9ZALe33pBuDY79X6lj\n"
"qznEMoJ3Jj+2+0YFKa7ivUuIY9sr3eCq6GWZA6oclwzZWj4lvUN4CBySt4Nbcfe6\n"
"qS9uGrVS8kHWa3wZ8jbJ\n"
"-----END PRIVATE KEY-----";

const char pico_az_id_scope[] = "[ID Scope]";

const char pico_az_COMMON_NAME[] = "[custom-hsm-device]";

const char pico_az_CERTIFICATE[] = 
"-----BEGIN CERTIFICATE-----""\n"
"-----END CERTIFICATE-----";

const char pico_az_PRIVATE_KEY[] = 
"-----BEGIN PRIVATE KEY-----""\n"
"-----END PRIVATE KEY-----";

const char pico_az_securityTypeEnvironmentVariable[] = ""; // Input either 'connectionString' or 'DPS'

const char pico_az_connectionStringEnvironmentVariable[] = "";

const char pico_az_dpsIdScopeEnvironmentVariable[] = "[IOTHUB_DEVICE_DPS_ID_SCOPE]";
