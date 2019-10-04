# mcuterminaltranslator  
Library for parsing commands for communication of MCUs  
Packet structure: 
```
<type+len, 1byte><checksum, 2bytes><payload>
```
max len: 63 bytes  
types:  
command: 0b1;  
var: 0b10;  
array: 0b11;
  
Structure of first byte:  
```
ttllllll
```
where: t - type bits; l - len bits  
id of array or variable will be at first byte of payload
