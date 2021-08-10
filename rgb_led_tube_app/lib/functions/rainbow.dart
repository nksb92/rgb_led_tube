import 'package:flutter/material.dart';
import 'package:flutter/services.dart';

class rainbow extends StatefulWidget {
  const rainbow({Key? key}) : super(key: key);

  @override
  _rainbow_state createState() => _rainbow_state();
}

class _rainbow_state extends State<rainbow> {
  final GlobalKey<FormState> formKey = GlobalKey();
  String shift = "";
  bool isChecked = false;
  double _currentSliderValue = 50;

  void save() {
    int int_shift = 0;
    double delay = _currentSliderValue;
    // build method in root class

    if (shift.length > 0) {
      int_shift = int.parse(shift);
    }
    print(int_shift);
    print(delay);
  }

  @override
  Widget build(BuildContext context) {
    return Container(
      child: Form(
        key: formKey,
        child: Column(
          mainAxisSize: MainAxisSize.min,
          children: <Widget>[
            Row(
              children: [
                Expanded(
                  flex: 1,
                  child: SizedBox(
                    child: Padding(
                      padding: const EdgeInsets.all(8.0),
                      child: TextFormField(
                        keyboardType: TextInputType.number,
                        inputFormatters: <TextInputFormatter>[
                          FilteringTextInputFormatter.digitsOnly,
                          LengthLimitingTextInputFormatter(3),
                        ],
                        decoration: const InputDecoration(
                            labelText: "Shift", helperText: "0-255"),
                        onChanged: (String txt) => shift = txt,
                        onFieldSubmitted: (String txt) => save(),
                      ),
                    ),
                  ),
                ),
              ],
            ),
            Row(
              children: <Widget>[
                Expanded(
                    flex: 1,
                    child: Padding(
                      padding: EdgeInsets.all(8.0),
                      child: const Text(
                        "Delay:",
                        style: const TextStyle(
                          fontSize: 16,
                          color: Colors.white60,
                        ),
                        textAlign: TextAlign.center,
                      ),
                    )),
                Expanded(
                  flex: 4,
                  child: Slider(
                    value: _currentSliderValue,
                    min: 1,
                    max: 255,
                    divisions: 255,
                    label: _currentSliderValue.round().toString(),
                    onChanged: (double value) {
                      setState(
                        () {
                          _currentSliderValue = value;
                        },
                      );
                    },
                  ),
                )
              ],
            ),
            Padding(
              padding: const EdgeInsets.only(bottom: 16.0, top: 8.0),
              child: ElevatedButton(
                onPressed: save,
                child: const Icon(Icons.send),
              ),
            )
          ],
        ),
      ),
      padding: const EdgeInsets.all(8.0),
    );
  }
}
