<div align="center">
  <img src="https://github.com/FerTia8/cpp-image-processing/blob/main/input/mandelbrot.png?raw=true" style="object-fit:contain;weight:200px;height:200px"}>
</div>
<h1 align="center">cpp-image-processing</h1>
<p align="center"><strong>Project whose aim is to represent and process RGB color images with 8-bits per RGB channel.</strong>


## Basic Info 📝
- <b>Language</b>: C++
- <b>Institution</b>: <a href="https://sigarra.up.pt/feup/pt/web_page.inicial">FEUP</a>
- <b>Course Unit</b>: <a href="https://sigarra.up.pt/feup/en/ucurr_geral.ficha_uc_view?pv_ocorrencia_id=501671">PROG</a> (Programming, L.EIC009) 
- <b>Starting Date</b>: 20/04/2023
- <b>Deadline</b>: 19/05/2023
- <b>Project Grade</b>: -/-
- <b>Authors</b>:
  - Bruno Coutinho Pereira (up202206351@fe.up.pt);
  - Ricardo Alexandre Alves Ramos (up202206349@fe.up.pt);
  - Tiago Fernando da Costa Ferreira (up202207311@fe.up.pt);
  
<h2>Install and Run ⬇️</h2>
Setting up the project is fairly easy and only a few steps are needed. <br></br>

- Make sure you have git installed on your computer by running:
```sh
$ git --version
```
  > If not, follow the instructions on the official <a href="https://git-scm.com/book/en/v2/Getting-Started-Installing-Git">documentation page</a>. 

- Clone the repository:
```sh
$ git clone https://github.com/FerTia8/cpp-image-processing
```

- Enter the `cpp-image-processing` directory. You should know take a look at the files the project was based on and modified by the team: `Color.cpp`, `Image.cpp`, `Script.cpp`, `XPM2.cpp`, and the respective header (`.h`) files. <a href="https://en.wikipedia.org/wiki/Object_code">Compile</a> the files:
```sh
$ make
```
  > Compilation should run without errors.

- You are now provided with three files that you can use to test the functionality of the program:
  - ```runscript```: processes one or more image processing scripts located on the ```scripts``` folder:<br></br>
  
  ```sh
  $ ./runscript scripts/<script_file1.txt> scripts/<script_file2.txt> (...) 
  ```
  
  - ```test```: file used to test each command. Pass no arguments to run all tests.<br></br>
  ```sh
  $ ./test <open> <blank> <save> <invert> <to_gray_scale> <replace> <h_mirror> <v_mirror> <add> <crop> <rotate_left> <rotate_left> <rotate_right> <median_filter> <xpm2_open> <xpm2_save>
  ```
  
  - ```benchmark```: times each function and logs the result on ```benchmarks.txt```:<br></br>
  ```sh
  $ ./benchmark
  ```

## Project status ⌛
- <b>21/04/2023</b>: First Setup.
- <b>23/04/2023</b>: Developing of Color, Image and Script.
- <b>27/04/2023</b>: Developing of Advanced Functionality.
- <b>15/05/2023</b>: Bug Fixing and Performance Tweaks have started.
- <b>16/05/2023</b>: Implementation of a CI/CD Automation Tool for Error Detection and Benchmarking.
- <b>17/05/2023</b>: Finishing README/Documentation and Commenting.
- <b>19/05/2023</b>: Delivery! ✅

## Learnings 📖
- Consolidated our knowledge in the <b>C++</b> Language;
- Improved <b>File Manipulation</b> skills;
- First hands-on Maintaining a Project as a Team using <b>Git</b>;
- Developed <b>Team</b> Working skills;
- Used benchmark and profiling tools for code optimization and memory leak prevention;
- Learnt new C++ Standard Library;

<h2>Copyright</h2>

See LICENSE.
