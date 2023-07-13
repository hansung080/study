# Hello Make
## Download Makefile
```sh
$ curl -fsSL 'https://raw.githubusercontent.com/hansung080/study/master/c/examples/hello-make/Makefile' | sed "s/hello-make/${TARGET:-change-me}/g" > "Makefile"
```