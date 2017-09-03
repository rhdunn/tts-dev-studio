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

#include "TtsDevStudioWindow.hpp"

#include <audio/TDSAudioDecoder.hpp>
#include <audio/TDSWaveformView.hpp>

void
TtsDevStudioWindow::ondecodefinished()
{
	waveformView->setAudioBuffer(decoder->audioBuffer());
}

TtsDevStudioWindow::TtsDevStudioWindow(const QStringList &arguments)
	: decoder(new TDSAudioDecoder(this))
	, waveformView(new TDSWaveformView(this))
{
	connect(decoder, SIGNAL(finished()), this, SLOT(ondecodefinished()));

	resize(700, 500);

	setCentralWidget(waveformView);

	if (arguments.size() > 1) {
		decoder->decode(arguments[1]);
	}
}
