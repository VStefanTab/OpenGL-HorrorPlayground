del main.exe
gcc -g main.c Robot\Robot.c Textures\textures.c House\House.c Hills\Hills.c -IC:\msys64\ucrt64\include\GL -LC:\msys64\ucrt64\lib -lSOIL -lfreeglut -lglu32 -lopengl32 -lm  -o main.exe >errors.txt 2>&1
main.exe