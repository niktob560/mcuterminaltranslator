# mcuterminaltranslator  
Library for parsing commands for communication of MCUs  
## Package structure: 
### For multidevice systems:
```
<type+len, 1 byte><checksum, 2 bytes><payload, len + 1 bytes>
```
### For 1-1 systems:
```
<type+len, 1 byte><checksum, 2 bytes><payload, len bytes>
```
  
## Payload structure:
### For multidevice systems:
```
<device id, 1 byte><data, len bytes>
```
### For 1-1 systems:
```
<data, len bytes>
```
### max len: 63 bytes  
  
## Types:  
command: ``0b1``;  
var: ``0b10``;  
array: ``0b11``;
  
## Structure of zero byte:  
```
ttllllll
```
where: t - type bits; l - len bits  
id of array or variable will be at first byte of payload
Max len of cmd: 1 byte(255 commands)  
Min len of array/variable: 2 bytes
  
## Structure of checksum generation:
```
sum of all bytes + 1
```
