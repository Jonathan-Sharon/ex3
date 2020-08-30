# ex3 assignment - Advanced Programming 1

In this assignment we implement a cache manager that solves 3 problems:

1. addition and multipication of metrixes.
2. rotating a bmp image and converting bmp image to gray scale.
3. calculating Hash on binary strings. 

## Design
In this project, in addition to the Bmp and Matrix classes that we implemented in the last assignment (ex2) we implement the following classes:

1. ***CacheOperation*** - this is an abstract class. it is used as an intreface to classes that describes methods which the cache manager supports. Every class that inherits from this class have to implement the following methods:

	* getInfo - returns a string that contains information about the operation that the class describes. For example if we would like to multiply matrix A by matrix B then the method will return "matrix multipication Hash(A) Hash(B)". The cache manager will use this string to compare between different operations. The function writes the hashes of the files instead of their path's in the string so we could check if another file contains the same information as one of the files used in the operation and to verify that the files didn't change (when the cache compering the opertion's infos to check whether or not we already made this operation). The chance that two files would have the same hash is **very** low so we assume that the diffrent files would have diffrent hash values.
	
	* operate - returns an output file that contains represention of the result of the operation that the object describes.

2. ***MatrixAddition*** - this class is a sub class of CacheOperation. It describes the addition of 2 matrixes.

3. ***MatrixMultipication*** - this class is a sub class of CacheOperation. It describes the multipication of 2 matrixes.

4. ***BmpConvertToGrayScale*** - this class is a sub class of CacheOperation. It describes the operation of converting bmp image to gray scale.

5. ***BmpRotate*** - this class is a sub class of CacheOperation. It describes the operation of rotating bmp image by 90 degrees clockwise.

6. ***GetBinaryStringHash*** - this class is a sub class of CacheOperation. It describes the Hash calculation on binary strings (using CRC32).

7. ***CacheOperationFactory*** - in this project we use **factory design pattern** to decide which CacheOperation we need to construct. the CacheOperationFactory is incharge of constructing the CacheOperation object according to the terminal arguments.

#### CacheManager

The CacheManager class is incharge of managing the data stored in the cache. The Cache stores results of the latest operations, so we wouldn't have to calculate the same operation if we already calculated it recently. The cache saves the data on a .txt file so the data will be saved between difrrent runs of the program. Each operation is represented by a CacheOperation object. The format that an operation is represented in the .txt file: <operationObject.getInfo()> <resultFile> <time stamp>. For example the addition of matrix A and matrix B will look like this: matrix addition Hash(A) Hash(B) resultFilePath 22/08/2020 23:14.
When we want to do an operation the CacheManager checks if the operation exists in the file (compares the getInfo) and if it does then it returns the result and update the time stamp. if it doesn't exists in the file then it calculates the result (using the operation's operate function), returns it and inserts it to the file.

The cache can save up to 10 results and if it reaches it's limit then it delets the least recently used result (checks using the time stamp) and replaces it with the new result.
the CacheManager contains the following methods:

1. clear - earesing all the data from the cache.
2. search - searches an operation in the cache and prints wether it found it using stdout.
3. operate - gets an CacheOperation object and returns a file reoresenting the result.


#### SOLID

The program meets the SOLID conditions.
***S*** - every module, class or function in a our program has single responsibility over a single part of that program's functionality - The Factpry is in charge of creating the object, the CacheManager is in charge of managing the cache, and the CacheOperations defines the action.

***O*** - Also, if we'd like to add more functions, the current code won't have to be modified. If we'd like to add another function, all we'd need to is to add a new class which inherents CacheOperation.

***L*** - As described, CacheOperation may be replaced with all of his sub-class.

***I*** - As seen, no class is forced implement methods it does not use.

***D*** -  In all of our classes, we do not not depend upon the implementations of the function/classes we use.

