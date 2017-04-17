## Project info ##
For eclipse:

Well, you need to configure project for Eclipse like:

```bash
mkdir eclipse
cd eclipse
cmake -G "Eclipse CDT4 - Unix Makefiles" -DCMAKE_BUILD_TYPE=Debug ..
```
or 
```bash
cmake -G "Eclipse CDT4 - Unix Makefiles" -DCMAKE_BUILD_TYPE=Release ..
```

For CLion:

- just import project and you're fine
