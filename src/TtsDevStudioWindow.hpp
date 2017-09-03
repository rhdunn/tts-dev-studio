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

#ifndef TTSDEVSTUDIOWINDOW_HPP
#define TTSDEVSTUDIOWINDOW_HPP

#include <QMainWindow>

class TDSAudioDecoder;
class TDSWaveformView;

class TtsDevStudioWindow
	: public QMainWindow
{
	Q_OBJECT;

	TDSAudioDecoder *decoder;
	TDSWaveformView *waveformView;
private slots:
	void
	ondecodefinished();
public:
	TtsDevStudioWindow(const TtsDevStudioWindow &) = delete;
	TtsDevStudioWindow &operator=(const TtsDevStudioWindow &) = delete;

	explicit
	TtsDevStudioWindow(const QStringList &arguments);
};

#endif
