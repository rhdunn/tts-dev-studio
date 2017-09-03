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

#ifndef AUDIO_TDSWAVEFORMVIEW_HPP
#define AUDIO_TDSWAVEFORMVIEW_HPP

#include <QWidget>
#include <QAudioBuffer>

/**
 * The @c TDSWaveformView class visualizes an audio waveform.
 */
class TDSWaveformView
	: public QWidget
{
	Q_OBJECT;
private:
	void
	paintEvent(QPaintEvent *event) override;

	void
	paintS16(QPaintEvent *event);

	QAudioBuffer buffer;
	decltype(&TDSWaveformView::paintEvent) painter;
public:
	TDSWaveformView(const TDSWaveformView &) = delete;
	TDSWaveformView &operator=(const TDSWaveformView &) = delete;

	/**
	 * Construct a @c TDSWaveformView instance parented to @p parent.
	 */
	explicit
	TDSWaveformView(QWidget *parent = nullptr);

	/**
	 * Sets the audio buffer being visualized to @p buffer.
	 *
	 * Returns @c true if the audio buffer can be visualized, or @c false if it cannot.
	 */
	bool
	setAudioBuffer(const QAudioBuffer &buffer);

	/**
	 * Returns the audio buffer being visualized.
	 */
	QAudioBuffer
	audioBuffer() const;
};

#endif
