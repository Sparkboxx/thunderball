import processing.serial.*;

Serial port;  // The serial port
String[] m;
String input_str;
int lf = 10;    // Linefeed in ASCII
float lprop = 60.;
float dprop = 6;
float arm_len=100.;
float arm_wid=7;
int boxsize = 60;
float[] theta = {0.1, 0.3, 0.5, 1.2};
float body_x = 200;
float body_y = 200;
float axes_Ox;
float axes_Oy;
float yaw = 0.;
float pitch = 0.;
float roll = 0.;
float angle_x = 1.0;
float angle_y = 0.0;
float angle_z = 0.0;
int ndata = 200;
float[] data1 = new float[ndata];
float[] data2 = new float[ndata];
float[] data3 = new float[ndata];


void setup(){
size(800, 600, P3D);

  // In case you want to see the list of available ports
  println(Serial.list());
  
  // Using the first available port (might be different on your computer)
  port = new Serial(this, Serial.list()[0], 9600); 
  port.bufferUntil(lf); 
  /*for (int k=0;k<10;k++){
    port.readString();
    delay(1000);
    println("Dump " + k);
  } */
  body_x = width/3.;
  body_y = height/2.;
  axes_Ox = width*2./3.;
  axes_Oy = height*3.;
  frameRate(30);
  smooth();
  stroke(#000000);
}


void draw()
{
  background(#DDDDDD);
  stroke(0);
  draw_axes();
  float dtheta[] = {0.1, 0.2, 0.3, 0.4};
  int i;
  int data_frame = frameCount % ndata;
  
  /*  
  if (mousePressed) {
   angle_x = -2*PI*(mouseY - body_y)/height;
   angle_y = 2*PI*(mouseX - body_x)/width;
  } 
  else {
    angle_z = atan2(mouseY - body_y, mouseX - body_x);
  }

  yaw = angle_z;
  */
  
  angle_x = pitch;
  angle_y = roll;
  angle_z = yaw;
  
  pushMatrix();
  //angle += 0.05;
  translate(body_x, body_y);
  rotateX(angle_x);
  rotateY(angle_y);
  translate(-body_x, -body_y);

  drawDrone(yaw, pitch, roll);
  for (i=0; i<4; i++) {
  theta[i] += dtheta[i];
  }
  
  popMatrix();
  // data1[data_frame] = theta[1];
  data1[data_frame] = angle_x;
  data2[data_frame] = yaw;
  data3[data_frame] = angle_y;
  
  for (i=0; i<ndata; i++) {
    int index = (data_frame + 1 + i) % ndata;
    stroke(#00AAAA);
    point(axes_Ox + i, height*0.3 - (0.2*height)*(data3[index]+PI)/(2*PI));
    stroke(#0000FF);
    point(axes_Ox + i, height*0.6 - (0.2*height)*(data2[index]+PI)/(2*PI));
    stroke(#FF0000);
    point(axes_Ox + i, height*0.9 - (0.1*height)*(1+cos(data1[index])));
  }

}

void drawDrone(float yaw, float pitch, float roll)
{
  int i;
  float prop_center_x, prop_center_y;
  
  pushMatrix();
  translate(body_x, body_y);
  stroke(#AAAA00);
  line(0,0,0,0,0,100);
  stroke(0);
  rotate(yaw);
  rectMode(CENTER);
  fill(#55AA88);
  //noFill();
  box(boxsize, boxsize, boxsize/5.);
  translate(0,0,boxsize/10);
  fill(#333366);
  box(boxsize/2., boxsize/2., boxsize/5.);

  for (i=0; i<4; i++){
    fill(100+30*i,0,0);
    pushMatrix();
    //translate( (arm_len + boxsize)/2*cos(prop*PI/2), (arm_len + boxsize)/2*sin(prop*PI/2));
    //box(arm_len*cos(prop*PI/2) + arm_wid*sin(prop*PI/2), arm_len*sin(prop*PI/2) + arm_wid*cos(prop*PI/2), arm_wid);
    draw_arm(i);
    popMatrix();
    draw_propeller(i, pow(-1,i)*theta[i]);
  }
  popMatrix();
}

/* Given a value of "arm" in {0,1,2,3}, draw_arm() draws 
 * the armth arm of the drone.
 */
void draw_arm(int arm){
  float arm_center_x, arm_center_y, arm_center_z;
  arm_center_x = cos(arm*PI/2.) * (boxsize + arm_len)/2.;  // TODO: replace with arm_center = (boxsize + arm_len)/2.;
  arm_center_y = sin(arm*PI/2.) * (boxsize + arm_len)/2.;  //        rotate(arm*PI/2.); translate(arm_center, 0.);
  arm_center_z = -boxsize/10.;
  pushMatrix();
  translate(arm_center_x, arm_center_y, arm_center_z);
  box(arm_len*cos(arm*PI/2) + arm_wid*sin(arm*PI/2), arm_len*sin(arm*PI/2) + arm_wid*cos(arm*PI/2), arm_wid);  // TODO (cont): box(arm_len, arm_wid, arm_wid);
  popMatrix();
}

/* Draws propeller "prop" on the plane,
 * at an angle "theta" with the arm
 */
void draw_propeller(int prop, float theta){
  pushMatrix();
  float prop_center_x = (arm_len + boxsize/2)*cos(prop*PI/2);
  float prop_center_y = (arm_len + boxsize/2)*sin(prop*PI/2);
  translate(prop_center_x, prop_center_y);
  rotate(theta);
  ellipse(0, lprop/2,dprop,lprop);
  ellipse(0,-lprop/2,dprop,lprop);
  ellipse(0, 0, dprop, dprop);
  popMatrix();
}

/* Draws the axes for plotting data */
void draw_axes(){
  line(axes_Ox, height*0.9, width*0.95, height*0.9);
  line(axes_Ox, height*0.9, axes_Ox, height*0.65);
  line(axes_Ox, height*0.6, width*0.95, height*0.6);
  line(axes_Ox, height*0.6, axes_Ox, height*0.35);
  line(axes_Ox, height*0.3, width*0.95, height*0.3);
  line(axes_Ox, height*0.3, axes_Ox, height*0.05);
}


// Called whenever there is something available to read
void serialEvent(Serial port) {
  // Data from the Serial port is read in serialEvent() using the read() function and assigned to the global variable: val
  input_str = port.readString();
  // For debugging
  println( "Raw Input:" + input_str);
 
  setYawPitchRollFromString(input_str);
}


/* Normalizes an nbit-bit sized unsigned integer 
 * input to a float in [-1,1]
 */
float normalizeInput(int val, int nbits) {
  float norm = float(val)/pow(2,nbits-1) - 1.0;
  println(val + " - " + norm);
  return norm;
}

String[] match_string(String s){
  return s.split(" ");
  // return matchAll(s, "[^\d]([\d]*?)[^\d]");
}

void setYawPitchRollFromString(String console_line) {
  // String s = "gyro:1234,5333,3333" // Match this with the console output line
//  String console = "foofoofoo,123,123:123123123123,123";

  if ( console_line != null ){
    
  m = match_string(console_line);
 
  if ( m != null && int(m[0]) == 0 && m.length == 5){
  
  yaw -= normalizeInput(int(m[1]), 14);
  pitch -= normalizeInput(int(m[2]), 14);
  roll -= normalizeInput(int(m[3]), 14);
  println( "Angles: " + yaw + " - " + pitch + " - " + roll);

  yaw = (abs(yaw) % (2*PI))*(yaw/abs(yaw));
  pitch = (abs(pitch) % (2*PI))*(pitch/abs(pitch));
  roll = (abs(roll) % (2*PI))*(roll/abs(roll));
  println( "Angles: " + yaw + " - " + pitch + " - " + roll);
  }
}
}


