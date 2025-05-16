#ifndef _KOZLOVSKIY_LRS_6_PARENT_AUDIO_PLAYER_H
#define _KOZLOVSKIY_LRS_6_PARENT_AUDIO_PLAYER_H

#include <string>
using namespace std;

class AudioPlayer {
protected:
    string audioFormat;
    int bitrate;
    
public:
    AudioPlayer() : audioFormat(""), bitrate(0) {
        cout << "Default constructor AudioPlayer\n";
    }
    
    virtual ~AudioPlayer() {
        cout << "AudioPlayer destroyed\n";
    }
    
    string getAudioFormat() const { return audioFormat; }
    int getBitrate() const { return bitrate; }
    
    void setAudioFormat(const string& format) { audioFormat = format; }
    void setBitrate(int rate) { bitrate = rate; }
    
    virtual void playSample() const {
        cout << "Playing audio sample...\n";
    }
};

#endif // _KOZLOVSKIY_LRS_6_PARENT_AUDIO_PLAYER_H