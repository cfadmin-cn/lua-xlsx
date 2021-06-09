.PHONY : build

default :
	@echo "======================================="
	@echo "Please use 'make build' command to build it.."
	@echo "Please use 'make rebuild' command to build it.."
	@echo "======================================="

INCLUDES += -I../ -I../../ -I../../../ -I../../src -I/usr/local/include
LIBS = -L../ -L../../ -L../../../ -L/usr/local/lib
# CFLAGS = -Wall -O3 -fPIC --shared -DJEMALLOC -ljemalloc -Wl,-rpath,. -Wl,-rpath,.. -Wl,-rpath,/usr/local/lib
# CFLAGS = -Wall -O3 -fPIC --shared -DTCMALLOC -ltcmalloc -Wl,-rpath,. -Wl,-rpath,.. -Wl,-rpath,/usr/local/lib
CFLAGS = -Wall -O3 -fPIC --shared -Wl,-rpath,. -Wl,-rpath,.. -Wl,-rpath,/usr/local/lib

# 构建lxlsx.so依赖库
build:
	@$(CC) -o lxlsx.so lxlsx.c $(CFLAGS) $(INCLUDES) $(LIBS) -lcore -lxlsxio_read -lxlsxio_write
	@mv *.so ../