

void setup() {
  pinMode(2, OUTPUT);  // Plug 1
  pinMode(3, OUTPUT);  // Plug 2
  pinMode(5, OUTPUT);  // Plug 3
  pinMode(6, OUTPUT);  // Plug 4
  pinMode(8, OUTPUT);  // Plug 5
  pinMode(9, OUTPUT);  // Plug 6
  pinMode(A5, OUTPUT); // Plug 7
  pinMode(A4, OUTPUT); // Plug 8
}

void loop() {
  int outPin = A4;
  digitalWrite(outPin, HIGH);
  delay(500);
  digitalWrite(outPin, LOW);
  delay(500);
}
