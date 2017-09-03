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

#include "TDSWaveformView.hpp"

#include <QPainter>
#include <QPaintEvent>

#include <cmath>

template <typename T> float sample_to_float(T value);
template <> float sample_to_float(signed short value) { return (float)value / 32768; }
template <> float sample_to_float(float value) { return value; }

template <typename T> void
draw_frames(QPainter &painter, const T *frames, int frameCount, int windowSize, int width, int height)
{
	painter.scale((float)width / (frameCount / 2 / windowSize), 1);

	decltype(frames->left) upper = std::numeric_limits<decltype(frames->left)>::min();
	decltype(frames->left) lower = std::numeric_limits<decltype(frames->left)>::max();

	int midpoint = height / 2;
	for (int frame = 0, x = 0; frame != frameCount; ++frame) {
		upper = std::max(upper, frames->left);
		lower = std::min(lower, frames->left);
		++frames;

		if (frame % windowSize != 0)
			continue;

		painter.drawLine(
			x, (int)(midpoint - (std::abs(sample_to_float(upper)) * midpoint)),
			x, (int)(midpoint + (std::abs(sample_to_float(lower)) * midpoint)));

		upper = std::numeric_limits<decltype(frames->left)>::min();
		lower = std::numeric_limits<decltype(frames->left)>::max();
		++x;
	}
}

void
TDSWaveformView::paintEvent(QPaintEvent *event)
{
	if (painter == nullptr) return;
	(this->*painter)(event);
}

void
TDSWaveformView::paintS16(QPaintEvent *event)
{
	QPainter painter(this);
	draw_frames(painter, buffer.constData<QAudioBuffer::S16S>(), buffer.frameCount(), window_size, event->rect().width(), event->rect().height());
}

void
TDSWaveformView::paintF32(QPaintEvent *event)
{
	QPainter painter(this);
	draw_frames(painter, buffer.constData<QAudioBuffer::S32F>(), buffer.frameCount(), window_size, event->rect().width(), event->rect().height());
}

TDSWaveformView::TDSWaveformView(QWidget *parent)
	: QWidget(parent)
	, window_size(16)
{
	setAutoFillBackground(true);
}

bool
TDSWaveformView::setAudioBuffer(const QAudioBuffer &buffer)
{
	QAudioFormat::SampleType type = buffer.format().sampleType();
	int size = buffer.format().sampleSize();

	if (type == QAudioFormat::SampleType::SignedInt && size == 16) {
		painter = &TDSWaveformView::paintS16;
	} else if (type == QAudioFormat::SampleType::Float && size == 32) {
		painter = &TDSWaveformView::paintF32;
	} else {
		painter = nullptr;
		this->buffer = QAudioBuffer();
		return false;
	}

	this->buffer = buffer;
	update();
	return true;
}

QAudioBuffer
TDSWaveformView::audioBuffer() const
{
	return buffer;
}

void
TDSWaveformView::setWindowSize(int windowSize)
{
	window_size = windowSize;
	update();
}

int
TDSWaveformView::windowSize() const
{
	return window_size;
}
