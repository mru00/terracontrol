



SRC = TerraControl/Form1.cs TerraControl/Form1.Designer.cs TerraControl/Program.cs 
TARGET = TerraControlMono.exe



publish-zip:
	cd TerraControl/publish && zip -r TerraControl.zip *



run: $(TARGET) 
	mono $(TARGET) 



%.exe: $(SRC)
	gmcs $(SRC) -out:$@ -r:System.Windows.Forms.dll -r:System.Drawing.dll -r:System.Data

program: $(TARGET) 

copy: mount copy_aux umount

copy_aux:
	-cp "../mnt/Users/mru/Documents/Visual Studio 2005/Projects/TerraControl/TerraControl" . -R

mount:
	sudo mount /dev/sda1 ../mnt -o uid=1000,gid=1000

umount: 
	sudo umount ../mnt

install_mono:
	apt-get install 

.PHONY: copy copy_aux umount install_mono
