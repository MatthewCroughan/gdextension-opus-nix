extends Control



var audiostreamgeneratorplayback : AudioStreamGeneratorPlayback
var audiopacketsbuffer = [ ]

func _ready():
	$AudioStreamPlayer.play()
	audiostreamgeneratorplayback = $AudioStreamPlayer.get_stream_playback()

func setname(lname):
	set_name(lname)
	$Label.text = name

func _process(_delta):
	$ColorRect.visible = (len(audiopacketsbuffer) > 0)
	while len(audiopacketsbuffer) > 0 and audiostreamgeneratorplayback.get_frames_available() > 441:
		var packet = audiopacketsbuffer.pop_front()
		audiostreamgeneratorplayback.push_buffer($HandyOpusNode.decode_opus_packet(packet))
	
