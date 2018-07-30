Compile
-------
### linux or Windows without Powershellv5 ###
```Bash
    g++ -O3 GetpublicIP.cpp -o GetpublicIP -static
```

### Windows with Powershellv5 ###
```Bash
    g++ -D PSv5 -O3 GetpublicIP.cpp -o GetpublicIP -static
```