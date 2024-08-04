extends Control

const NOTES = [
	"C",
	"C#",
	"D",
	"D#",
	"E",
	"F",
	"F#",
	"G",
	"G#",
	"A",
	"A#",
	"B",
]

# Called when the node enters the scene tree for the first time.
func _ready():
	pass # Replace with function body.


# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta):
	pass


func get_note():
	return ($OctaveSlider.value + 1) * 12 + $PitchSlider.value


func get_velocity():
	return $VelocitySlider.value


func _on_octave_slider_value_changed(value):
	$OctaveSlider/Label.text = "%d" % value


func _on_pitch_slider_value_changed(value):
	$PitchSlider/Label.text = NOTES[value]


func _on_velocity_slider_value_changed(value):
	$VelocitySlider/Label.text = "%d" % value
