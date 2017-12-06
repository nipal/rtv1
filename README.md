
## Description
This raytracer displays the following objects: plane, sphere, cylinder, and cone. The lights are colored. We can place multiple cameras. The scenes are defined by a configuration file. The staining system is  [Phong](href="https://en.wikipedia.org/wiki/Phong_shading")

## Instalation
### Linux (based on Debian)

+ You will need X11 and libxext
+ and just `make` the project
```
	sudo apt-get install libx11
	sudo apt-get install libx11-dev
	sudo apt-get install libxext
	sudo apt-get install libxext-dev
	make
```


### Mac OSX
+ just `make` the project
```
    make
```

## utillisation

```
    ./rtv1 file_scene
```
| key | funciton |
|:----:|:----:|
| `a` | turn left |
| `d` | turn right |
| `s` |  turn up |
| `w` |  turn down|
| `up` | go front  |
| `down` | go back |
| `right` | go right |
| `left` | go left |
| `v` | visual debug mode on/off|
| `p` | print the camera parameter in console 
| `Tab` | switch camera| 
| `Esc` | quit the programe |

only in visual debug mode:
| mouse button | funciton |
|:----:|:----:|
| `left_button` | show normal of surface|
| `right_button` | show the ligne to the light |


## File_input format

#### General structure
```
object_name{
    objet_component object_value        # this is a comment
}

object_value: vector OR float
vector      : 2.0, .56, 0.
float       : 42.1337
```

#### Key_word
| key_word_object |
| :--- | 
| light |
| camera |
| plan |
| sphere |
| cylinder |
| cone |

| key_word_component | value type | 
| :--- | ---: | 
| pos | vector |
| col | vector |
| dir | vector |
| front | vector |
| up | vector |
| value | double |
| spec | double |

| component\object | light | camera | plan | sphere | cylinder | cone |
| :---: |:---: |:---: |:---: |:---: |:---: |:---: |
| pos | ✓ |  ✓ |  ✓ |  ✓ |  ✓ |  ✓ | 
| col | ✓ | |  ✓ |  ✓ |  ✓ |  ✓ | 
| dir | | |  ✓ |  ✓ |  ✓ |  ✓ | 
| value | | |  ✓ |  ✓ |  ✓ |  ✓ | 
| spec | | |  ✓ |  ✓ |  ✓ |  ✓ | 
| front | |  ✓ | | | | |
| up | |  ✓ | | | | |


####  Parsing behavior
- comment begin with `#` and ends at the end of the line
 - the blanc space are separator and several is the same as one
 - the order of the components has no influence
 - If you have a wrong name_object you got an error and the programe stop.
 - if you have a wrong name_composante the composente is ignored
 - if you have several time the same componante the laste is the selected
 - if you have a wrong vector or number parsing the value is 0
 - if you have a missing componante a default value is set
 - the color are caped betwen 0 and 255
 - if the speculare coeeficient `spec` is less than `3.0` it is ignored  


#### file examlpe
```
light
{
	pos		0, 0, 0
	col		255, 100, 50        # color
}

camera
{
	pos	0.000000, 0.000000, -10.000000
	dir		0, 0, 1
	up	0.685008, -0.576282, 0.445717
}

sphere
{
	pos		-2, 0, -2
	col		255, 0, 0
	value	0.5
	spec    6               # speculare coefficient more than 3
}
```

the scene are in the ***asset*** folder

## Image
![some object with white Light](https://image.noelshack.com/fichiers/2017/49/1/1512379936-screen-shot-2017-12-04-at-10-30-19-am.png)
![some object with colored light](https://image.noelshack.com/fichiers/2017/49/1/1512383169-screen-shot-2017-12-04-at-10-33-56-am.png)
![all abject and speculare](https://image.noelshack.com/fichiers/2017/49/1/1512383319-screen-shot-2017-12-04-at-11-28-11-am.png)
![debug view mode](https://image.noelshack.com/fichiers/2017/49/1/1512384256-screen-shot-2017-12-04-at-11-43-23-am.png)


