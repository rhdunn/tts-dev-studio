add_executable(tts-dev-studio
	"audio/TDSAudioDecoder.cpp"
	"audio/TDSWaveformView.cpp"
	"TtsDevStudioWindow.cpp"
	"main.cpp")
target_link_libraries(tts-dev-studio Qt5::Widgets Qt5::Multimedia)
