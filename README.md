
# PostgreSQL Enabler-Stopper

## Description
Tired of slow and paid heavy weight statistics apps for your simple regression tasks? Agux's Non Linear Plot Regressor is your solution for 1 variable non linear regression. You can use one of the many pre-loaded fitting functions or easily define your very own to suit your needs.
It is made with python libraries, is fast,  has intuitive interface, provides many metrics (R2, RMSE, Chi2) and parameter values standard deviations.
It uses scipy.optimize.curve_fit to make the iterative calculation by TRF method (Trusted Region). App commes with 4 different real life datasets that you can test.
<!-- ![screen-gif](./prueba_rando_creator.gif) -->
<!-- <img src="https://github.com/aguxone/agux_random_file_creator/blob/gif_storage/prueba_rando_creator.gif?raw=true" alt="agxu_rfc_gif" width="60%" height="40%"> -->
<img src="https://github.com/aguxone/agux_non_linear_plot_regressor/blob/gif-storage-branch/756x490.gif?raw=true" alt="agux_nlpr_gif" width="70%" height="40%">
<!-- <video src='https://user-images.githubusercontent.com/98858551/174418629-481619d3-27ed-48c0-b952-05b6239417b3.mp4'; width="100"; height="100"></video> -->
<!-- https://user-images.githubusercontent.com/98858551/174418629-481619d3-27ed-48c0-b952-05b6239417b3.mp4 -->
<!-- <video  style="display:block; width:10%; height:auto;" autoplay controls loop="loop">
       <source src=https://user-images.githubusercontent.com/98858551/174418629-481619d3-27ed-48c0-b952-05b6239417b3.mp4 type="video/mp4" />
</video> -->
<!-- <div style="width:100px ; height:100px>
       <video src='https://user-images.githubusercontent.com/98858551/174418629-481619d3-27ed-48c0-b952-05b6239417b3.mp4'></video>
<div/> -->

## Libraries used
- Matplotlib
- Numpy
- Scipy
- WxPython

## Opening the app:
- If using the source code, just run the .py file (previously having installed the necessary libraries)
- If using a windows standalone release, just open the .exe file , it was compiled with pyinstaller and it needs to load the python interpreter + libraries so this might take from 5secs to 2 min depending on your computer (be patient).

## Usage:
- Opening a file: Usen to open button to choose a .csv or .txt file, and choose the delimiter below. File must be a comma separated file (using comma or other delimiter) and must have 2 or 4 columns. First column is for the independent variable (x) , second column for the dependent variable (y), and third and fourth columns are for x and y error estimates respectively (one error per data instance).
- Error cols present? Using 2 columns file: If "Error cols present" is "No" the program will ask to assign a % of error to the x and y variables, it will assume you have only 2 column with X and Y data. This assignment is optional, since it is only used to display error bars, and to calculate a coherent chi2 statistic. If both % are zero, bars will not be plotted and chi2 square statistic will give and "inf" value.
- Plotting the data and fits: Just use the Plot button in order to plot the loaded file. Each time you click on plot or fit, a new plot will appear on the screen, coexisting with the previous plot. You can erase the plots by clicking on the "Clear" button (although it will clear all the plots). You can plot scatter points or a continuous plot by clicking on the appropiate boxes, nothing will show up until you click on "Plot" or "Fit". Parameter values and their standard deviations, Rsquared, RMSE and Chi2 statistics are displayed only for the latest fitted curve in the bottom right corner of the interface.
- Custom Cuve Fit: In the "Choose fit curve" section you can select the custom option and define your own curve, it is a requierement that you use python and numpy syntax, it has an "Instructions" button in order to succesfully fit your curve (don't worry it's quite simple). You can use up to 25 parameters, you can use the letters from a to z (except the x) and need to follow alphabetical order (e.g if you need 3 parameters you have to use a,b,c and not a,b,d ). The letter "x" will be the independent variable in your expression.

## Details about calculations:
- Itearative calculations for minimizing least squares are automated by scipy library (scipy.optimize.curve_fit) using Least Squares and TRF method. You can learn more in https://docs.scipy.org/doc/scipy/reference/generated/scipy.optimize.curve_fit.html
- Chi2 is calculated by using the following formula:

     $$ \chi^2 = \sum_{i=1}^{n}  ( \frac{y_i - \hat{y}}{\sigma_i})^2 $$
     
Where y_i are the data points, yhat is the predicted y point by the curve, and  sigma_i is the error estimate of the y_i value.
Degrees of freedom which constitute the expected value of the Chi2 distribution are calculated as DF = number of data point - number of parameters of the fitted curve .

- RMSE is calculated by using the following formula:

     $$ RMSE = \sqrt{ \frac{1}{n} \sum{(y_i - \hat{y})^2}} $$

Where y_i are the data points, yhat is the predicted y point by the curve, and  sigma_i is the error estimate of the y_i value.

## Example datasets:
Non linear regression is a tiny art where you need to know a bit about your function in order to use adequate initial parameters for the alogorithm to converge to a coherent answer. Change the following initial parameters for the provided example datasets to find an adequate curve:
- Gaussian: b=2
- Dampened Sine : d=15 , e =2.4
- Sine: a=4 , b=9
- glutation : defaults are ok for exponential curve

