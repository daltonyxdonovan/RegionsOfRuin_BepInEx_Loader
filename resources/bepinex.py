import os
import zipfile
print("thanks for using the loader!\n    <3 daltonyx")
print("setting the working directory")
os.chdir(os.path.dirname(os.path.abspath(__file__)))

print("setting the path to the plugins folder\n")

path = os.path.join(os.getenv('PROGRAMFILES(X86)'), 'Steam', 'steamapps', 'common', 'Regions Of Ruin')



print("copying contents of bepinex folder to plugins folder\n")
# copy the contents of the bepinex folder to the plugins folder
for file in os.listdir('bepinex'):
    print("copying " + file + " to " + path)
    os.replace(os.path.join('bepinex', file), os.path.join(path, file))
        
