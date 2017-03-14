# [ST080](https://github.com/tino1b2be/ST080)

The ST080 Dtum Machine is an Embedded Systems project that we did as part of EEE3074W course at UCT. We designed and built a prototype using concepts we had learnt in this course and other prerequisite courses. The full report of the project can be viewed [here](https://github.com/tino1b2be/ST080/blob/master/Docs/Project_Report_Final.pdf)...and a video of the finished product [here](https://youtu.be/f0DpraNo41Q)
## Background
Make great beats on the move; where you choose: A couple of the main advantages of a drum machine. The Drum Machine, in the context of this project, is an instrument that incorporates a drum set (Or multiple drum sets) and a recording machine to imitate the sounds of a drum kit when pads are struck. Drum Machines are often used by musicians, DJs or in general people who may not necessarily know how to play drums but are, however looking for a drum effect in the musical project they are busy with.
The aim of this project is to is conceptualize, design and implement a prototype drum machine that will demonstrate the full criteria of the EEE3074W design project.

## Concept
A Drum Machine is an electronic musical instrument that is designed to imitate the sound of drums, cymbals and other percussion instruments. Drum machines are used in many different avenues of life.  The use of a drum machine ranges from personal use to make nice sounding beats to professional commercial use by DJs.

## Design Overview
The design is based on the design of a very popular Rhythm Composer, the Roland TR-808, as seen in Figure 3. The TR-808 was one of the earliest programmable drum machines, with which users could create their own rhythms and beats.

The drum machine will incorporate four different instruments. Each instrument will have its own unique pre-recorded sample. The ST-080 will include a composer mode that allows for interactive beat creation. The user will be able to add an instrument to a channel rank while hearing the effects that it has on the beat. An example of this can be shown [here](https://www.youtube.com/watch?v=Cer1un9vciI). This feature is useful for people who cannot play the four instruments at the same time or for users that may not have the best drumming talent or rhythm. The drum machine will be given multiple modes in order to accommodate more features in a simple design.

## Prototype Overview
The prototype of the ST-080 will be similar to (just as the name is) yet more simple than the TR-808. The user will have one of two options when using the ST-080, namely Freestyle mode and composer mode. The ST-080 will not have all the tuning capabilities of the TR-808. While there is room for filters and amplifiers to be added this product will not include such is it is just a prototype.

The prototype will consist of a Housing box that contains button pads, and LCD screen, LEDs and potentiometers. It will have a row of buttons at the bottom that will be used for the channel rack. These GPIOs will simply set a pin high or low which will indicate whether the instrument is selected to be played. In the top right corner there will be for buttons that will be used as interrupts in Freestyle mode. Whenever these buttons are pressed a sound will almost immediately be played. 

The ST-080 prototype will have the following features:
*	Composer Mode: This is a mode which allows the user to make use of the channel rack to compose an instrumental. They do this by pressing the buttons to create patterns (called “scores”) for the different instruments available on the device. The channel rack itself is designed for music with a time signature of 4 beats per bar hence it has 1 bar or 4 beats with each beat divided into 4 to make 16 pattern keys. The ST080 loops this array when in composer mode.
*	Playback Mode: This mode allows the user to listen to any of the songs stored in the 16 slots provided on the ST080. Like the composer mode, the ST080 loops the channel rack when playing the music.
*	Freestyle Mode: This mode allows the user to play around with the instruments on the ST080 and create their own music without any restrictions on tempo, patterns and time signature. They simply hit a button and the sound plays.
*	Permanent Storage: The ST080 allows the user to store up to 16 songs. It does this by storing the musical scores that the user created rather than store the actual audio. This is more efficient because less storage space is needed and thus a cheaper storage device, like EEPROM, can be used to store music.
*	Varying Tempo: The user can compose music at different tempos ranging from 40 up to 140 beats per second by simply turning a tempo-potentiometer on the ST080.
*	Headphones Jack: The user has the option to plug in head phones or an external speaker system to either listen to the music in the headphones or connect to a larger sounds system. The output on the headphones jack has enough power to drive even the biggest studio headphones.
*	Feedback: The LCD displays text to help the user with certain functions of the ST080. It also provides feedback like when it is saving something, loading, if no song is stored on a specific slot, the current mode, etc…). There are LEDs to show which keys have been pressed on the channel rack, which mode the user is in, which instrument is being modified, which song is playing or when it is saving or resetting.
*	Visual Metronome: Instead of an audible metronome to help the user compose the music, a visual metronome was implemented instead. The LEDs on the channel rack will light up when that key is being played so the user can keep track of where on the channel rack the ST080 is playing music at and also where to add more scores as they wish.
*	Reset device: There is a button to restart the device without saving any unsaved changes made to the songs.
*	Clear all songs: There is a key combination that allows the user to delete all the songs stored in RAM. NB: the user would have to save if they want to remove these songs in the permanent storage too.

Many features are missing from the prototype due to time and budget constraints but there is space for all of them to be added if development of this device is to continue. 

## Images of the final product
![full](https://github.com/tino1b2be/ST080/raw/master/Docs/full.jpg)
![front](https://github.com/tino1b2be/ST080/raw/master/Docs/IMG_3402.jpg)
![side1](https://github.com/tino1b2be/ST080/raw/master/Docs/IMG_3401.jpg)
![side2](https://github.com/tino1b2be/ST080/raw/master/Docs/IMG_3399.jpg)
![lcd](https://github.com/tino1b2be/ST080/raw/master/Docs/IMG_3411.jpg)
![buttons1](https://github.com/tino1b2be/ST080/raw/master/Docs/IMG_3409.jpg)

## Project Contributors
* Tinotenda Chemvura (@tino1b2be)
* John Odetokun (@JohnOdetokun)
* Herman Kouassi (@h-kouame)
* Othniel Konan (@Kojey)

## License
This project is licensed under the [MIT License](https://github.com/tino1b2be/ST080/blob/master/LICENSE)
