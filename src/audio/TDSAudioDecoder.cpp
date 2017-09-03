/*
 * Copyright (C) 2017 Reece H. Dunn
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, see: <http://www.gnu.org/licenses/>.
 */

#include "TDSAudioDecoder.hpp"

void
TDSAudioDecoder::onbufferready()
{
	QAudioBuffer buffer = decoder->read();

	if (data.size() == 0) {
		format = buffer.format();

		// If a duration estimate is unavailable (-1), the buffer will grow
		// normally, instead of being reserved upfront.
		qint64 duration = decoder->duration();
		if (duration != -1) {
			// If the audio's μs duration is not an even multiple of 1,000 the
			// conversion to ms can round down the value, ignoring the μs part.
			// Therefore, this adds an extra ms to compensate.
			++duration;

			// Convert from QAudioDecoder::duration units (ms) to
			// QAudioBuffer::duration units (μs).
			duration *= 1000;

			qint32 bytes = format.bytesForDuration(duration);
			data.reserve(bytes);
		}
	}

	data.append(buffer.constData<char>(), buffer.byteCount());
}

void
TDSAudioDecoder::onfinished()
{
	finished();
}

void
TDSAudioDecoder::onerror(QAudioDecoder::Error)
{
	error(decoder->errorString());
}

TDSAudioDecoder::TDSAudioDecoder(QObject *parent)
	: QObject(parent)
	, decoder(new QAudioDecoder(this))
{
	connect(decoder, SIGNAL(bufferReady()), this, SLOT(onbufferready()));
	connect(decoder, SIGNAL(finished()), this, SLOT(onfinished()));
	connect(decoder, SIGNAL(error(QAudioDecoder::Error)), this, SLOT(onerror(QAudioDecoder::Error)));
}

bool
TDSAudioDecoder::decode(const QString &filename)
{
	if (decoder->state() != QAudioDecoder::StoppedState)
		return false;

	data.resize(0);

	decoder->setSourceFilename(filename);
	decoder->start();
	return true;
}

bool
TDSAudioDecoder::decode(QIODevice *device)
{
	if (decoder->state() != QAudioDecoder::StoppedState)
		return false;

	data.resize(0);

	decoder->setSourceDevice(device);
	decoder->start();
	return true;
}

QAudioBuffer
TDSAudioDecoder::audioBuffer() const
{
	if (data.size() == 0)
		return QAudioBuffer();
	return QAudioBuffer(data, format);
}
