#ifndef WAVEFILE_H
#define WAVEFILE_H
#include <stdint.h>

typedef struct WaveFile {
	uint32_t Chunk_ID;
	uint32_t ChunkSize;
	uint32_t Format;

	uint32_t SubChunk1ID;
	uint32_t SubChunk1Size;
	uint16_t AudioFormat;
	uint16_t NumberOfChanels;
	uint32_t SampleRate;
	uint32_t ByteRate;

	uint16_t BlockAlignment;
	uint16_t BitsPerSecond;

	uint32_t SubChunk2ID;
	uint32_t SubChunk2Size;

	char data[];
} WAV_HEADER;
#endif
