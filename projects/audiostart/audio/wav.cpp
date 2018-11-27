// WAV-loading example
// Source code from http://www.dunsanyinteractive.com/blogs/oliver/?p=72
// Copyright (c) 2011 Oliver Plunkett

#include <iostream>
#include "wav.h"

/*
 * Struct that holds the RIFF data of the Wave file.
 * The RIFF data is the meta data information that holds,
 * the ID, size and format of the wave file
 */
struct RIFF_Header
{
        char chunkID[4];
        int chunkSize; //size not including chunkSize or chunkID
        char format[4];
};

/*
 * Struct to hold fmt subchunk data for WAVE files.
 */
struct WAVE_Format
{
        char subChunkID[4];
        int subChunkSize;
        short audioFormat;
        short numChannels;
        int sampleRate;
        int byteRate;
        short blockAlign;
        short bitsPerSample;
};

/*
 * Struct to hold the data of the wave file
 */
struct WAVE_Data
{
        char subChunkID[4]; //should contain the word data
        int subChunk2Size; //Stores the size of the data block
};

/*
 * Load wave file function. No need for ALUT with this
 */
bool loadWavFile(const std::string filename, ALuint* buffer)
{
	int ret = 0;
    ALsizei* size = nullptr;
    ALsizei* frequency = nullptr;
    ALenum format = 0;
    //Local Declarations
    FILE* soundFile = nullptr;
    WAVE_Format wave_format;
    RIFF_Header riff_header;
    WAVE_Data wave_data;
    unsigned char* data;

    try {
        soundFile = fopen(filename.c_str(), "rb");
        if (!soundFile) {
            throw("File does not exist");
		}
//        std::cout << "File exists" << std::endl;

        // Read in the first chunk into the struct
        ret = fread(&riff_header, sizeof(RIFF_Header), 1, soundFile); if (!ret) { }

        //check for RIFF and WAVE tag in memeory
        if ((riff_header.chunkID[0] != 'R' || riff_header.chunkID[1] != 'I'
                || riff_header.chunkID[2] != 'F'
                || riff_header.chunkID[3] != 'F')
                || (riff_header.format[0] != 'W' || riff_header.format[1] != 'A'
                        || riff_header.format[2] != 'V'
                        || riff_header.format[3] != 'E')) {
            throw("Invalid RIFF or WAVE Header");
        } else {
//            std::cout << "Valid header" << std::endl;
        }

        //Read in the 2nd chunk for the wave info
        ret = fread(&wave_format, sizeof(WAVE_Format), 1, soundFile); if (!ret) { }
        //check for fmt tag in memory
        if (wave_format.subChunkID[0] != 'f' || wave_format.subChunkID[1] != 'm'
                || wave_format.subChunkID[2] != 't'
                || wave_format.subChunkID[3] != ' ') {
            throw("Invalid Wave Format");

        } else {
//            std::cout << "Valid format" << std::endl;
        }
        //check for extra parameters;
        if (wave_format.subChunkSize > 16)
            fseek(soundFile, sizeof(short), SEEK_CUR);

        //Read in the the last byte of data before the sound file
        ret = fread(&wave_data, sizeof(WAVE_Data), 1, soundFile); if (!ret) { }
        //check for data tag in memory
        if (wave_data.subChunkID[0] != 'd' || wave_data.subChunkID[1] != 'a'
                || wave_data.subChunkID[2] != 't'
                || wave_data.subChunkID[3] != 'a') {
            throw("Invalid data header");
        } else {
//            std::cout << "Valid data header" << std::endl;
        }
        //Allocate memory for data
        data = new unsigned char[wave_data.subChunk2Size];

        // Read in the sound data into the soundData variable
        if (!fread(data, wave_data.subChunk2Size, 1, soundFile)) {
            throw("error loading WAVE data into struct!");
        } else {
//            std::cout << "Loaded into struct" << std::endl;
        }

        //Now we set the variables that we passed in with the
        //data from the structs
        size = &wave_data.subChunk2Size;
//        std::cout << "Size" << std::endl;
        frequency = &wave_format.sampleRate;

//        std::cout << "Size and freq set" << std::endl;
        //The format is worked out by looking at the number of
        //channels and the bits per sample.
        if (wave_format.numChannels == 1) {
//            std::cout << "Single channel" << std::endl;
            if (wave_format.bitsPerSample == 8)
                format = AL_FORMAT_MONO8;
            else if (wave_format.bitsPerSample == 16)
                format = AL_FORMAT_MONO16;
        } else if (wave_format.numChannels == 2) {
            if (wave_format.bitsPerSample == 8)
                format = AL_FORMAT_STEREO8;
            else if (wave_format.bitsPerSample == 16)
                format = AL_FORMAT_STEREO16;
        }

//        std::cout << "Format set" << std::endl;
        //create our openAL buffer and check for success
        alGenBuffers(1, buffer);
//        std::cout << "Created buffer" << std::endl;

        //now we put our data into the openAL buffer and
        //check for success
        alBufferData(*buffer, format, (void*) data, *size, *frequency);
        //errorCheck();
        //clean up and return true if successful
        fclose(soundFile);
//        std::cout << "Closing file" << std::endl;
        return true;
    } catch (const char* error) {
        //our catch statement for if we throw a string
        std::cerr << error << " : trying to load " << filename << std::endl;
        //clean up memory if wave loading fails
        if (soundFile != nullptr)
            fclose(soundFile);
        //return false to indicate the failure to load wave
        return false;
    }
}
