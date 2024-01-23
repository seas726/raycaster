#ifndef UTIL_H_
#define UTIL_H_

class utility {

    public:

    static const float clampValue(float value) {
        if(value > 1) {
            return 1.0f;
        }
        else if(value < 0)
        {
            return 0.0f;
        }
        return value;
    }
};

#endif