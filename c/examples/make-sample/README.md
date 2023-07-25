# Make Sample
## Download Makefile
Before downloading Makefile, set the `TARGET_NAME`:
```sh
TARGET_NAME='your target name'
```

To download `Makefile for a binary project`, run:
```sh
curl -fsSL 'https://raw.githubusercontent.com/hansung080/study/master/c/examples/make-sample/bin.mk' | sed "s/make-sample/${TARGET_NAME:-change-me}/g" > 'bin.mk'
```

Or, to download `Makefile for a library project`, run:
```sh
curl -fsSL 'https://raw.githubusercontent.com/hansung080/study/master/c/examples/make-sample/lib.mk' | sed "s/make-sample/${TARGET_NAME:-change-me}/g" > 'lib.mk'
```

Before downloading Makefile, set the `PROJECT_TYPE`:
```sh
PROJECT_TYPE='bin | lib'
```

To download `Makefile for each project`, run:
```sh
curl -fsSL 'https://raw.githubusercontent.com/hansung080/study/master/c/examples/make-sample/project.mk' | sed "s/bin\.mk/${PROJECT_TYPE:-change-me}.mk/g" > 'Makefile'
```
