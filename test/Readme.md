## Makefile

Command | Description
--------|-------------
make                | compile all objects and tests
make clean          | remove all objects and tests
make clean-objects  | remove all objects
libphysengine.so    | create dynamic library

Note: objects are created to src and utils folders
## Test
### Run all tests
```
  ./TestAll.sh

```

### Run also memory leak tests (valgrind must be installed)

```
  ./TestAll.sh valgrind
```
