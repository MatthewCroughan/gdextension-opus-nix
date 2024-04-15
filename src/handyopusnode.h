#ifndef HANDYOPUSNODE_H
#define HANDYOPUSNODE_H

#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/variant/utility_functions.hpp>
#include <godot_cpp/classes/audio_effect_capture.hpp>

#include "opus.h"
#include "spsc_jitter_buffer.h"
#include "speex/speex_resampler.h"

namespace godot {

class HandyOpusNode : public Node {
	GDCLASS(HandyOpusNode, Node)

private:
	double time_passed;

    int _last_opus_error = 0;
    int _last_resampler_error = 0;

    OpusDecoder* _opus_decoder;
    OpusEncoder* _opus_encoder;
    

    int _last_opus_errorE = 0;
    int _last_resampler_errorE = 0;
    SpeexResamplerState* _resamplerE;
    PackedVector2Array _sample_bufE;


    SpeexResamplerState* _resampler;
    PackedVector2Array _sample_buf;

    const int GODOT_SAMPLE_RATE = 44100;
    const int OPUS_FRAME_SIZE = 480;
    const int OPUS_SAMPLE_RATE = 48000;
    const int CHANNELS = 2;
    const int RESAMPLING_QUALITY = 10; // 0 to 10
    const int DEFAULT_BITRATE = 24000; // bits / second from 500 to 512000
    const int EXPECTED_PACKET_LOSS = 5; // percentage from 0 to 100

    SPSCJitterBuffer jitter_buffer;


protected:
	static void _bind_methods();

public:
	HandyOpusNode();
	~HandyOpusNode();

    PackedVector2Array decode_opus_packet(const PackedByteArray&);
    PackedByteArray encode_opus_packet(PackedVector2Array samples);
   
    PackedByteArray _sample_buf_to_packet(PackedVector2Array samples);

};





class VOIPInputCaptureE : public AudioEffectCapture {
    GDCLASS(VOIPInputCaptureE, AudioEffectCapture)

protected:
    static void _bind_methods();

private:
    int _last_opus_error = 0;
    int _last_resampler_error = 0;
    OpusEncoder* _opus_encoder;
    SpeexResamplerState* _resampler;
    PackedVector2Array _sample_buf; // Resample audio here before sending through opus

public:
    PackedByteArray _sample_buf_to_packet(PackedVector2Array samples);

    // Constants

    const int GODOT_SAMPLE_RATE = 44100;
    const int OPUS_FRAME_SIZE = 480;
    const int OPUS_SAMPLE_RATE = 48000;
    const int CHANNELS = 2;
    const int RESAMPLING_QUALITY = 10; // 0 to 10
    const int DEFAULT_BITRATE = 24000; // bits / second from 500 to 512000
    const int EXPECTED_PACKET_LOSS = 5; // percentage from 0 to 100


    // Properties

    bool muted = false;
    float volume = 1; // [0, 1]


    // Property Set / Get

    void set_muted(const bool _muted) { muted = _muted; }
    bool is_muted() const { return muted; }

    void set_volume(const float _volume) { volume = _volume; } // Error condition for outside [0,1]?
    float get_volume() const { return volume; }

    void set_bitrate(const int _bitrate);
    int get_bitrate() const;


    // Methods

    VOIPInputCaptureE();
    ~VOIPInputCaptureE();

    void send_test_packets();

};



}

#endif // HANDYOPUSNODE_H
