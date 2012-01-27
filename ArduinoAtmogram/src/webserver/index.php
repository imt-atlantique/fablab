<!--
Log data send by Arduino Atmogram project and display it with JS chart.

To view:
	[yourserver]/arduino

To put data:
	[yourserver]/arduino/index.php?temp=20&humi=50

Florian Lissot & Victor Jolissaint
@ FabLab Telecom Bretagne 2012.
-->

<html>
	<head>
		<title>Arduino Atmogram</title>
		<script type="text/javascript" src="js/jscharts.js"></script>
	</head>
	<body>
		<div id="graph" style="text-align: center;">Loading graph...</div>

		<?php
			/* Vars */
			
			// You must to create a file (data.csv) and allow read and write on it
			// Do 'touch data.csv' and 'chmod 777 data.csv'
			$file = "data.csv"; 
			$values = array ();
			$dataArrayHumidity="";
			$dataArrayTemp="";

			/* Find the last index of csv file */
			$lastLine = `tail -n 1 $file`;
			if(isset($lastLine)){
				$index = explode(";", $lastLine);
				$index = $index[0];
			}
			else{
				$index = 0;
			}

			/* Get param */
			if($_GET){
				$temp = $_GET['temp'];
				$humi = $_GET['humi'];

				if(isset($temp) && isset($humi)) {

					/* Write the values in the csv file */
					file_put_contents($file, ++$index.";".$temp.";".$humi."\n", FILE_APPEND | LOCK_EX);
						// using the FILE_APPEND flag to append the content to the end of the file
						// and the LOCK_EX flag to prevent anyone else writing to the file at the same time		
				}
				else{
					echo "Error: invalid parameter";
				}
			}

			/* Open the csv file */
			$f = fopen($file, 'rb');
			
			/* Parse the csv file */
			while (($data = fgetcsv($f, 5000, ";")) != FALSE) {
				$values[$data[0]] = $data;
			}  

			/* Set DataArray */
			foreach( $values as $key => $value){
				$dataArrayHumidity .= "[".$key.",".$value[2]."],";
			}
			$dataArrayHumidity = rtrim($dataArrayHumidity, ","); //remoe the last coma

			foreach( $values as $key => $value){
				$dataArrayTemp .= "[".$key.",".$value[1]."],";
			}
			$dataArrayTemp = rtrim($dataArrayTemp, ","); //remove the last coma
		?>

		<script type="text/javascript">
			var myChart = new JSChart('graph', 'line');
			
			/* Humidity chart */
			myChart.setDataArray([<?php echo $dataArrayHumidity; ?>], 'blue');
			
			/* Temp chart */
			myChart.setDataArray([<?php echo $dataArrayTemp; ?>], 'green');
			
			myChart.setAxisPaddingBottom(50);
			myChart.setAxisPaddingLeft(60);
			myChart.setTextPaddingBottom(10);
			myChart.setAxisValuesNumberY(5);
			myChart.setIntervalStartY(0);
			myChart.setIntervalEndY(100);
			//myChart.setAxisValuesNumberX(5);
			//myChart.setShowXValues(false);
			myChart.setTitle("Arduino Atmogram");
			myChart.setAxisColor('#656565');
			myChart.setAxisNameColor('#4A4A4A');
			myChart.setAxisNameFontSize(10);
			myChart.setAxisNameX('Temps');
			myChart.setAxisNameY('');
			myChart.setTitleColor('#454545');
			myChart.setAxisValuesColor('#454545');
			myChart.setLineColor('#A4D314', 'green');
			myChart.setLineColor('#BBBBBB', 'gray');
			<?php for($i=1;$i<=$index;$i++) { echo "myChart.setTooltip([".$i."]);"; } ?>
			myChart.setFlagColor('#9D16FC');
			myChart.setFlagRadius(4);
			myChart.setBackgroundImage('chart_bg.jpg');
			myChart.setSize(616, 321);
			myChart.setLegendShow(true);
			myChart.setLegendPosition(490, 10);
			myChart.setLegendForLine('blue', 'Humidity');
			myChart.setLegendForLine('green', 'Temperature');
			myChart.draw();
		</script>
	</body>
</html>