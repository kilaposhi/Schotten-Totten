# Big Shotten-Totten

### Manip git à faire :

`git clone https://github.com/kilaposhi/Shotten-Totten.git` : Pour copier le repository sur vos machines  


- Créer un fichier `.gitignore` contenant les fichiers de configurations. Voici un exemple pour mon fichier qui utilise l'IDE Clion :
```
cmake-build-debug/
CMakeLists.txt
.idea/
```
> Ce fichier indique à git, les fichiers OU directory à ne pas mettre sur le Github.   
> On inclut donc toutes les librairies, les "CMake" etc...  

Comme le repository github est **publique**, tout le monde pourrait accéder à notre projet et on ne veut pas que le monde ait accès à nos fichiers de config pour une question de sécurité. 