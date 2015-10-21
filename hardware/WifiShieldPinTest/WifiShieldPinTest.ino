

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
  digitalWrite(2, HIGH);
  digitalWrite(3, HIGH);
  digitalWrite(5, HIGH);
  digitalWrite(6, HIGH);
  digitalWrite(8, HIGH);
  digitalWrite(9, HIGH);
  digitalWrite(A5, HIGH);
  digitalWrite(A4, HIGH);
  delay(500);
  digitalWrite(2, LOW);
  digitalWrite(3, LOW);
  digitalWrite(5, LOW);
  digitalWrite(6, LOW);
  digitalWrite(8, LOW);
  digitalWrite(9, LOW);
  digitalWrite(A5, LOW);
  digitalWrite(A4, LOW);
  delay(500);
  
}
