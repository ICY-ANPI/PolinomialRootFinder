# PolinomialRootFinder
Este proyecto tiene implementado el método de deflación polinomial, el metodo de Muller y el metodo de LaGuerre para busqueda de raices. Ademas tiene pruebas unitarias realizadas en el marco de boost
***

##1. Requisitos
***
Para poder utilizar este programa usted debera contar con la siguiente biblioteca de boost (probado con la version 1.66):

[DOWNLOAD BOOST](http://www.boost.org/users/download/)

adicionalmente usted deberá descomprimir el contenido e ingresar en la carpeta descomprimida usando la terminal.
una vez allí deberá instalar cierta parte del contenido para ello utilice lo siguientes comandos:

```console
foo@bar:~$ sudo apt-get --purge remove libboost-all-dev
foo@bar:~$ ./bootstrap.sh --with-libraries=atomic,date_time,exception,filesystem,iostreams,locale,program_options,regex,signals,system,test,thread,timer,log
foo@bar:~$ sudo ./b2 install
```
## Compilación:
***
Para realizar una compilación completa del  programa puede utilizar el siguiente comando: 
```console
foo@bar:~$ ./compile_all
```
El comando internamente realiza una limpieza de la carpeta build donde se crea el código y el compilado

## Ejecución:
***
- ### Test
Para realizar la bateria de pruebas utilice el siguiente comando: 
```console
foo@bar:~$ ./do_tests
```
- ### Benchmark
Para realizar el benchmark utilice el siguiente comando: 
```console
foo@bar:~$ ./benchmark_code
```
- ### User Input
Para usar el programa que lee la entrada del usuario utilice el siguiente comando: 
```console
foo@bar:~$ ./user_input
```
- ###Borrar compilado
para borrar todo rastro  de archivos compilados utilice el siguiente comando:
```console
foo@bar:~$ ./execute_order_66
```
