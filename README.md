# x64dbgResolveAPIArray
A basic x64dbg plugin which will resolve an array of API pointers.

## Background
Most modern malware will attempt to thwart static analysis by using dynamic API resolution in conjunction with API hashing.<br />
Often after these APIs have been resolved by the malware they pointers to each API will be placed in an array for future use.<br />
This plugin was simply written to resolve all the APIs pointers in the array so they can be filled in as a struct or array in your static code anlysis tool of choice.<br />

## Setup
Place the .dp32 file in the plugins directory of your x32 version of x64dgb.<br />
Run the command "pluginload resolveAPIArray" in the command window of 32 bit x64dbg.<br />

## Plugin Use
Run the following command in 32 bit x64dbg "resolveAPIArray \<starting address of array\>, \<number of entries in array\>".<br />
Example: resolveAPIArray 0x0019DD88, 2<br />
The resolved APIs will appear in the log output along with pointer address and offset from the starting address.<br />
A CSV will also be generated with this information in the same directory as your 32 bit x64dbg binary.<br />
