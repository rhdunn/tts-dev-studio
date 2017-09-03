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

#ifndef AUDIO_TDSAUDIODECODER_HPP
#define AUDIO_TDSAUDIODECODER_HPP

#include <QAudioDecoder>

class QIODevice;

/**
 * The @c TDSAudioDecoder class allows decoding audio.
 *
 * NOTE: @c QAudioDecoder is marked as under development and subject to change.
 * This @c TDSAudioDecoder class wraps @c QAudioDecoder to restrict handling
 * any changes to the implementation of @c TDSAudioDecoder, and to provide an
 * API better suited to the @c tts-dev-studio use cases.
 */
class TDSAudioDecoder
	: public QObject
{
	Q_OBJECT;

	QAudioDecoder *decoder;
	QAudioFormat format;
	QByteArray data;
private slots:
	void
	onbufferready();

	void
	onfinished();

	void
	onerror(QAudioDecoder::Error error);
signals:
	/**
	 * Signals that the decoding has finished successfully.
	 *
	 * If decoding fails, the @c error signal is emitted instead.
	 */
	void finished();

	/**
	 * Signals that an @c error has occurred.
	 */
	void error(QString error);
public:
	TDSAudioDecoder(const TDSAudioDecoder &) = delete;
	TDSAudioDecoder &operator=(const TDSAudioDecoder &) = delete;

	/**
	 * Construct a @c TDSAudioDecoder instance parented to @p parent.
	 */
	explicit
	TDSAudioDecoder(QObject *parent = nullptr);

	/**
	 * Decode the audio in @p filename.
	 *
	 * Returns @c false if another decode operation is in progress. Otherwise,
	 * @c true is returned and decoding @p filename is started.
	 */
	bool
	decode(const QString &filename);

	/**
	 * Decode the audio in @p device.
	 *
	 * Returns @c false if another decode operation is in progress. Otherwise,
	 * @c true is returned and decoding @p device is started.
	 */
	bool
	decode(QIODevice *device);

	/**
	 * Returns the decoded audio buffer if available.
	 *
	 * Returns an invalid buffer if no audio has been decoded, or on failure.
	 *
	 * You should respond to the @c finished() signal before calling
	 * @c audioBuffer() to make sure you get useful data.
	 */
	QAudioBuffer
	audioBuffer() const;
};

#endif
