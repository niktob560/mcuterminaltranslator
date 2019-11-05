# mcuterminaltranslator  
Library for parsing commands for communication of MCUs  
## Package structure: 
```
<type+len, 1byte><checksum, 2bytes><payload>
```
max len: 63 bytes  
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
