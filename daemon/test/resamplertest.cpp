/*
 *  Copyright (C) 2004, 2005, 2006, 2008, 2009, 2010 Savoir-Faire Linux Inc.
 *  Author: Alexandre Savard <alexandre.savard@savoirfairelinux.com>
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 *
 *  Additional permission under GNU GPL version 3 section 7:
 *
 *  If you modify this program, or any covered work, by linking or
 *  combining it with the OpenSSL project's OpenSSL library (or a
 *  modified version of that library), containing parts covered by the
 *  terms of the OpenSSL or SSLeay licenses, Savoir-Faire Linux Inc.
 *  grants you additional permission to convey the resulting work.
 *  Corresponding Source for a non-source form of such a combination
 *  shall include the source code for the parts of OpenSSL used as well
 *  as that of the covered work.
 */

#include <iostream>
#include <algorithm>
#include <math.h>

#include "resamplertest.h"

void ResamplerTest::setUp()
{

}

void ResamplerTest::tearDown()
{

}

void ResamplerTest::testUpsamplingRamp()
{
    // generate input samples and store them in inputBuffer
    generateRamp();

    std::cout << "Test Upsampling Ramp" << std::endl;
    SamplerateConverter converter(44100);

    performUpsampling(converter);

    LowSmplrBuffer tmpInputBuffer;
    HighSmplrBuffer tmpOutputBuffer;

    std::copy(inputBuffer.begin(), inputBuffer.begin() + tmpInputBuffer.size(), tmpInputBuffer.begin());
    std::cout << "Input Buffer" << std::endl;
    for(int i = 0; i < tmpInputBuffer.size(); i++)
        std::cout << tmpInputBuffer[i] << ", ";
    std::cout << std::endl;

    std::copy(outputBuffer.begin(), outputBuffer.begin() + tmpOutputBuffer.size(), tmpOutputBuffer.begin());
    std::cout << "Output Buffer" << std::endl;
    for(int i = 0; i < tmpOutputBuffer.size(); i++)
        std::cout << tmpOutputBuffer[i] << ", ";
    std::cout << std::endl;
}

void ResamplerTest::testDownsamplingRamp()
{
    generateRamp();

    std::cout << "Test Downsampling Ramp" << std::endl;
    SamplerateConverter converter(44100);

    performDownsampling(converter);

    HighSmplrBuffer tmpInputBuffer;
    LowSmplrBuffer tmpOutputBuffer;

    std::copy(inputBuffer.begin(), inputBuffer.begin() + tmpInputBuffer.size(), tmpInputBuffer.begin());
    std::cout << "Input Buffer" << std::endl;
    for(int i = 0; i < tmpInputBuffer.size(); i++)
        std::cout << tmpInputBuffer[i] << ", ";
    std::cout << std::endl;

    std::copy(outputBuffer.begin(), outputBuffer.begin() + tmpOutputBuffer.size(), tmpOutputBuffer.begin());
    std::cout << "Output Buffer" << std::endl;
    for(int i = 0; i < tmpOutputBuffer.size(); i++)
        std::cout << tmpOutputBuffer[i] << ", ";
    std::cout << std::endl;
}

void ResamplerTest::testUpsamplingTriangle()
{
    generateTriangularSignal();

    std::cout << "Test Upsampling Triangle" << std::endl;
    SamplerateConverter converter(44100);

    performUpsampling(converter);

    LowSmplrBuffer tmpInputBuffer;
    HighSmplrBuffer tmpOutputBuffer;

    std::copy(inputBuffer.begin(), inputBuffer.begin() + tmpInputBuffer.size(), tmpInputBuffer.begin());
    std::cout << "Input Buffer" << std::endl;
    for(int i = 0; i < tmpInputBuffer.size(); i++)
        std::cout << tmpInputBuffer[i] << ", ";
    std::cout << std::endl;

    std::copy(outputBuffer.begin(), outputBuffer.begin() + tmpOutputBuffer.size(), tmpOutputBuffer.begin());
    std::cout << "Output Buffer" << std::endl;
    for(int i = 0; i < tmpOutputBuffer.size(); i++)
        std::cout << tmpOutputBuffer[i] << ", ";
    std::cout << std::endl;
}

void ResamplerTest::testDownsamplingTriangle()
{
    generateTriangularSignal();

    std::cout << "Test Downsampling Triangle" << std::endl;
    SamplerateConverter converter(44100);

    performDownsampling(converter);

    HighSmplrBuffer tmpInputBuffer;
    LowSmplrBuffer tmpOutputBuffer;

    std::copy(inputBuffer.begin(), inputBuffer.begin() + tmpInputBuffer.size(), tmpInputBuffer.begin());
    std::cout << "Input Buffer" << std::endl;
    for(int i = 0; i < tmpInputBuffer.size(); i++)
        std::cout << tmpInputBuffer[i] << ", ";
    std::cout << std::endl;

    std::copy(outputBuffer.begin(), outputBuffer.begin() + tmpOutputBuffer.size(), tmpOutputBuffer.begin());
    std::cout << "Output Buffer" << std::endl;
    for(int i = 0; i < tmpOutputBuffer.size(); i++)
        std::cout << tmpOutputBuffer[i] << ", ";
    std::cout << std::endl;
}
void ResamplerTest::testUpsamplingSine()
{
    // generate input samples and store them in inputBuffer
    generateSineSignal();

    std::cout << "Test Upsampling Sine" << std::endl;
    SamplerateConverter converter(44100);

    performUpsampling(converter);

    LowSmplrBuffer tmpInputBuffer;
    HighSmplrBuffer tmpOutputBuffer;

    std::copy(inputBuffer.begin(), inputBuffer.begin() + tmpInputBuffer.size(), tmpInputBuffer.begin());
    std::cout << "Input Buffer" << std::endl;
    for(int i = 0; i < tmpInputBuffer.size(); i++)
        std::cout << tmpInputBuffer[i] << ", ";
    std::cout << std::endl;

    std::copy(outputBuffer.begin(), outputBuffer.begin() + tmpOutputBuffer.size(), tmpOutputBuffer.begin());
    std::cout << "Output Buffer" << std::endl;
    for(int i = 0; i < tmpOutputBuffer.size(); i++)
        std::cout << tmpOutputBuffer[i] << ", ";
    std::cout << std::endl;
}

void ResamplerTest::testDownsamplingSine()
{
    // generate input samples and store them in inputBuffer
    generateSineSignal();

    std::cout << "Test Downsampling Sine" << std::endl;
    SamplerateConverter converter(44100);

    performDownsampling(converter);

    HighSmplrBuffer tmpInputBuffer;
    LowSmplrBuffer tmpOutputBuffer;

    std::copy(inputBuffer.begin(), inputBuffer.begin() + tmpInputBuffer.size(), tmpInputBuffer.begin());
    std::cout << "Input Buffer" << std::endl;
    for(int i = 0; i < tmpInputBuffer.size(); i++)
        std::cout << tmpInputBuffer[i] << ", ";
    std::cout << std::endl;

    std::copy(outputBuffer.begin(), outputBuffer.begin() + tmpOutputBuffer.size(), tmpOutputBuffer.begin());
    std::cout << "Output Buffer" << std::endl;
    for(int i = 0; i < tmpOutputBuffer.size(); i++)
        std::cout << tmpOutputBuffer[i] << ", ";
    std::cout << std::endl;
}

void ResamplerTest::generateRamp()
{
    for(int i = 0; i < inputBuffer.size(); i++) {
        inputBuffer[i] = (SFLDataFormat)i;
    }
}

void ResamplerTest::generateTriangularSignal()
{
    for(int i = 0; i < inputBuffer.size(); i++) {
        inputBuffer[i] = (SFLDataFormat)(i*10);
    }
}

void ResamplerTest::generateSineSignal()
{
    for(int i = 0; i < inputBuffer.size(); i++) {
        inputBuffer[i] = (SFLDataFormat)(1000.0 * sin((double)i));
    }
}

void ResamplerTest::performUpsampling(SamplerateConverter &converter)
{
    LowSmplrBuffer tmpInputBuffer;
    HighSmplrBuffer tmpOutputBuffer;

    int i, j;
    for(i = 0, j = 0; i < (inputBuffer.size() / 2); i += tmpInputBuffer.size(), j += tmpOutputBuffer.size()) {
        std::copy(inputBuffer.begin() + i, inputBuffer.begin() + tmpInputBuffer.size() + i, tmpInputBuffer.begin());
        converter.resample(tmpInputBuffer.data(), tmpOutputBuffer.data(), tmpOutputBuffer.size(), 8000, 16000, tmpInputBuffer.size());
        std::copy(tmpOutputBuffer.begin(), tmpOutputBuffer.end(), outputBuffer.begin() + j);
    }
}

void ResamplerTest::performDownsampling(SamplerateConverter &converter)
{
    HighSmplrBuffer tmpInputBuffer;
    LowSmplrBuffer tmpOutputBuffer;

    int i, j;
    for(i = 0, j = 0; i < inputBuffer.size(); i += tmpInputBuffer.size(), j += tmpOutputBuffer.size()) {
        std::copy(inputBuffer.begin() + i, inputBuffer.begin() + tmpInputBuffer.size() + i, tmpInputBuffer.begin());
        converter.resample(tmpInputBuffer.data(), tmpOutputBuffer.data(), tmpOutputBuffer.size(), 16000, 8000, tmpInputBuffer.size());
        std::copy(tmpOutputBuffer.begin(), tmpOutputBuffer.end(), outputBuffer.begin() + j);
    }
}