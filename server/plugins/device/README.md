# Device Notes

## Orders
There are 4 orders for hardware part

|Value|Description|
|---|---|
|0| Identification - hub only - returns list of connected devices|
|1| Read - device only, returns value from specified channel |
|2| Write - device only, sets value and returns value from specified channel|
|3| Response - device only, order for Read and Write response |

## Frame descriptor
Frame descriptor is 8 bit value that contains:

|Size | Description|
|---|---|
|3 b| Order |
|5 b| Address in hub (0..30), hub itself is a device avaliable on address 31|

## Frame structure
Frame looks like:

|Size| Description |
|---|---|
|1 B| Size of frame |
|1 B| Descritor |
|0-253 B| Payload |

For payload specific info take a look on READMEs for specific plugins, but generally pattern looks like:

|Size| Description|
|---|---|
|1 B| Channel address |
|? B| Channel specific payload |

### Identification
This frame is fixed, and looks like:
###### Request:
> { 0x01, 0x00 }
###### Response:
|Size|Description|
|---|---|
|1 B| Size|
|3 B per device | Device adrress (1B) + Device type (2B)|

### Read, Write and Response
These are device specific, but generally pattern is:

|Size| Description|
|---|---|
|1B| Size|
|1B| Descritor |
|0..252B| Payload|
