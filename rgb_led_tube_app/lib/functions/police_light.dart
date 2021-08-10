import 'package:flutter/material.dart';

class police_light extends StatefulWidget {
  const police_light({Key? key}) : super(key: key);

  @override
  _police_light_state createState() => _police_light_state();
}

class _police_light_state extends State<police_light> {
  void save() {
    print("Police Light");
  }

  @override
  Widget build(BuildContext context) {
    return Container(
        child: Padding(
      padding: const EdgeInsets.only(bottom: 16.0, top: 8.0),
      child: ElevatedButton(
        onPressed: save,
        child: const Icon(Icons.send),
      ),
    ));
  }
}
