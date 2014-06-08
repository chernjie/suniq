# Suniq

Faster version of `sort | uniq -c | sort -n[r]`

### Example
```shell
$ cat list | suniq
$ cat list | suniq -r
```

### Installation
```shell
$ ./configure && make && make install
```

If you use brew on MacOSX 
```shell
$ brew install suniq
```

### Acknowledgement
- @alisaifee - [suniq.cpp](https://gist.github.com/alisaifee/2983201)
- @hyperair - [suniq.cpp](https://gist.github.com/hyperair/5489942)

