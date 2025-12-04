<div style="position: fixed; top: 50%; left: 50%; transform: translate(-50%, -50%);">
	<h1>Example webpage</h1>
	<div>
		<table>
			<?php
				$file = fopen('data.txt', 'r');
				while(($line = fgets($file)) !== false):
        			list($key, $value) = explode(':', $line, 2);
					$key = trim($key);
					$value = trim($value);
			?>
				<tr><td><?=$key?></td><td><?=$value?></td></tr>
			<?php
				endwhile;
    			fclose($file);
			?>
		</table>
	<div>
</div>
