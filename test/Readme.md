### Test
* Contains unit tests for Physicsengine
* Shared object file, libphysengine, is created here by default


## Makefile

Command | Description
--------|-------------
make                | compile all objects and tests
make clean          | remove all objects and tests
make clean-objects  | remove all objects
libphysengine.so    | create dynamic library

Note: objects are created to src and utils folders
## Running tests
Make sure execute permissions have been granted to TestAll.sh shell script. This can be done for example with:
```
sudo chmod u+x TestAll.sh
```


### Run all tests
```
  ./TestAll.sh

```

### Run also memory leak tests (valgrind must be installed)

```
  ./TestAll.sh valgrind
```
