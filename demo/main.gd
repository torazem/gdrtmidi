extends Node

@onready var rtmidiout = $GDRtMidiOut

const disconnected_color = Color("#b5b5b5")
const connected_color = Color("#18d921")

var playing_notes = []

func _ready():
	rtmidiout.initialize(0, "Testing")
	var current_api = rtmidiout.get_current_api()
	$MidiApiLabel.text = "%d" % current_api

	$Port/StatusColor.color = disconnected_color

	rtmidiout.send_message(PackedByteArray([192, 1]))
	rtmidiout.send_message(PackedByteArray([144, 64, 90]))
	#rtmidiout.send_test_message()

#############################################################

func note_on(note, velocity):
	rtmidiout.send_message(PackedByteArray([144, note, velocity]))

func note_off(note):
	rtmidiout.send_message(PackedByteArray([128, note]))

func change_program(program):
	rtmidiout.send_message(PackedByteArray([192, program]))

#############################################################

func _on_port_connect_button_pressed():
	var selected_port_index = $Port/PortDropDown.selected
	if selected_port_index > -1:
		var selected_port = $Port/PortDropDown.get_item_id(selected_port_index)
		rtmidiout.open_port(selected_port, "RtMidi Output")
		$Port/StatusColor.color = connected_color
		$Port/Label.text = $Port/PortDropDown.get_item_text(selected_port_index)

func _on_port_disconnect_button_pressed():
	rtmidiout.close_port()
	$Port/StatusColor.color = disconnected_color
	$Port/Label.text = ""

func _on_port_refresh_button_pressed():
	var n_ports = rtmidiout.get_port_count()
	$Port/PortDropDown.clear()
	for i in range(n_ports):
		$Port/PortDropDown.add_item(rtmidiout.get_port_name(i), i)

#############################################################

func _on_program_change_button_pressed():
	print($Program/ProgramSlider.value)
	$Program/Label.text = "%d" % $Program/ProgramSlider.value

#############################################################

func _on_play_note_button_button_down():
	for note_selector in [$Notes/NoteSelector1, $Notes/NoteSelector2, $Notes/NoteSelector3]:
		var note = note_selector.get_note()
		var velocity = note_selector.get_velocity()
		playing_notes.append(note)
		note_on(note, velocity)

func _on_play_note_button_button_up():
	for playing_note in playing_notes:
		note_off(playing_note)

#############################################################
