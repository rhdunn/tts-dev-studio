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

	const auto *frames = buffer.constData<QAudioBuffer::S16S>();
	int frameCount = buffer.frameCount();

	painter.scale((float)event->rect().width() / (frameCount / 2), 1);

	int midpoint = event->rect().height() / 2;
	for (int frame = 0; frame != frameCount; ++frame) {
		float value = ((float)std::abs(frames->left) / 32768.0f);
		++frames;

		painter.drawLine(frame, (int)(midpoint - (value * midpoint)), frame, (int)(midpoint + (value * midpoint)));
	}
}

TDSWaveformView::TDSWaveformView(QWidget *parent)
	: QWidget(parent)
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
