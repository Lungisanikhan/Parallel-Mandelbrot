#include <fstream>
#include <iostream>
#include<chrono>
using namespace std;


/*
while (x * x + y * y < 2 * 2 and iteration < max_iteration) {
   
	 xtemp = x * x - y * y +x0
    y= 2*x*y +y0
	x =xtemp
	 iteratio


}
*/

int findMandelbrot(double cr, double ci, int max_iterations) {

	int i = 0;
	double zr = 0.0, zi = 0.0;

	while (i < max_iterations && zr * zr + zi * zi < 4.0) {
		
		double temp = zr * zr - zi * zi + cr;
		zi = 2.0 * zr * zi + ci;
		zr = temp;
		i++;
	}
	return i;
}
double mapToReal(int x, int imageWidth,double minR,double maxR){

	double range = maxR - minR;

	//[0,width]
	//[0, maxR -minR] - val *range/width
	//[minR, maxR] - last step + minR

	return x * (range / imageWidth) + minR;


}

double mapToImaginary(int y, int imageHeight, double minI, double maxI){

	double range = maxI - minI;

	return y * (range / imageHeight) + minI;

}

int main() {
	auto start = std::chrono::steady_clock::now();
	//get the reqyured input values from file
	//ifstream fin("input.txt");

	int imageWidth=1080, imageHeight=1080, maxN=100000;
	double minR=0, maxR=1.7 , minI=-1.0, maxI=1.0;
	/*
	if (!fin) {
		cout << "Could not open file!" << endl;
		cin.ignore();

		return 0;
	}
	fin >> imageWidth >> imageHeight>>maxN;
	fin >> minR >> maxR >> minI >> maxI;
	//printf(minI);
	fin.close();
	*/
	//open the output file, write the ppm header
	ofstream fout("output_image.ppm");
	fout << "P3" << endl; //"Magic Number" - PPM File
	fout << imageWidth << " " << imageHeight << endl; //dimensions
	fout << "256" << endl; //max value of pixel r,g,b value

	// For every pixel
	  
	for (int y = 0; y < imageHeight; y++) { //rows..
		for (int x = 0; x < imageWidth; x++) { //pixels in row
			//for the real and imag values for c, corresponding

	//to that x, y pixel in the image
			double cr = mapToReal(x, imageWidth, minR, maxR);
			double ci = mapToImaginary(y, imageHeight, minI, maxI);


	// ...find the number of iterations in the mandelbrot formula
	// using said c.
			int n = findMandelbrot(cr, ci, maxN);

//map the resulting nuber to the rgb value
			int r = (n % 256); //change for more interesting values!
			int g = (n % 256); //change for more interesting values!
			int b = (n% 256); //change for more interesting values!

			int maxRGB = 256;
			int max3 = maxRGB * maxRGB * maxRGB;
			double t = (double)n / (double)maxN;
			n = (int)(t * (double)max3);
			//b = n / (maxRGB * maxRGB);
			int nn = n - b * maxRGB * maxRGB;
			//r = nn / maxRGB;
			//g = nn - r * maxRGB;
			// ... output it to the image

			fout << r << " " << g << " " << b << " ";


		}
		fout << endl;
	}
	auto end = std::chrono::steady_clock::now();
	std::chrono::duration<double> elapsed_seconds = end - start;
	fout.close();
	std::cout << "elapsed time to compute in serial without GPU /OpenMP : " << elapsed_seconds.count() << "s\n";
	cout << "Finished!" << endl;

	return 0;
	
}