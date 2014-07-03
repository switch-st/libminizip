libminizip
==========

zip压缩/解压库（zlib库minizip的重新编译）

地址
	https://github.com/switch-st/libminizip.git

说明
 * zlib是Jean-loup Gailly、Mark Adler开发的zip格式压缩解压库，minizip是利用zlib接口实现简单的压缩解压程序。
 * 该库只是为zlib库minizip写了一个Makefile，将其编译为动态库，未对zlib及minizip做任何更改。
 * 该库可以满足大部分压缩解压需求，比直接利用zlib要方便简单一些。
 *
 * 从zlib官网(http://www.zlib.net/)上下载最新zlib源码。
 * 解压zlib，并将git下的Makefile拷贝到zlib/contrib/minizip目录下。
 * 在zlib目录下编译zlib(./configure && make)。
 * 在minizip目录下，用新的Makefile编译libminizip，生成libminizip.so库。
 * git下的test.c是使用示例，将其拷贝到zlib/contrib/minizip，执行make test编译，可以进行测试。
 * 示例代码使用的是zlib 1.2.8版本的源码，如后续版本minizip接口有变化，不保证示例代码可以继续使用。
 * 开发过程中依赖zlib库的zlib.h，以及minizip的crypt.h、ioapi.h、iowin32.h、mztools.h、unzip.h、zip.h等头文件，libminizip不依赖libz.so
 * 
 * 欢迎补充。

调用
	调用方法详见test.c以及minizip.c、miniunz.c。

			by switch
			switch.st@gmail.com

