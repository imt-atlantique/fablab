<?php
//function to get unread mails
function check_email($username, $password) { 
    //url to connect to
    $url = "https://mail.google.com/mail/feed/atom"; 

    //sending request 
    $curl = curl_init();
    curl_setopt($curl, CURLOPT_URL, $url);
    curl_setopt($curl, CURLOPT_FOLLOWLOCATION, 1);
    curl_setopt($curl, CURLOPT_RETURNTRANSFER, 1);
    curl_setopt($curl, CURLOPT_SSL_VERIFYPEER, false);
    curl_setopt($curl, CURLOPT_USERPWD, $username .":". $password);
    curl_setopt($curl, CURLOPT_HTTPAUTH, CURLAUTH_BASIC);
    curl_setopt($curl, CURLOPT_ENCODING, "");
    $curlData = curl_exec($curl);
    curl_close($curl);
	
    //returning retrieved feed
    return $curlData;
}

//function to truncate a string 
function truncate($text, $length) {
	return strlen($text) > $length ? substr($text, 0, $length - 3) .'...' : $text;
}

//function to strip accents in a string 
function stripAccents($text) {
	return str_replace(
		array('à','â','ä','á','ã','å','î','ï','ì','í','ô','ö','ò','ó','õ','ø','ù','û','ü','ú','é','è','ê','ë','ç','ÿ','ñ',
			'À','Â','Ä','Á','Ã','Å','Î','Ï','Ì','Í','Ô','Ö','Ò','Ó','Õ','Ø','Ù','Û','Ü','Ú','É','È','Ê','Ë','Ç','Ÿ','Ñ'),
		array('a','a','a','a','a','a','i','i','i','i','o','o','o','o','o','o','u','u','u','u','e','e','e','e','c','y','n', 
			'A','A','A','A','A','A','I','I','I','I','O','O','O','O','O','O','U','U','U','U','E','E','E','E','C','Y','N'),
		$text);
}

//making page to behave like xml document
header('Content-Type:text/xml; charset=UTF-8');

try {
	$xml = "<response>\n";
	
	//getting current time
	$xml .= "\t<time>". date('H:i') ."</time>\n";

	//calling mail function
	$feed = check_email("LOGIN_GMAIL", "PASSWORD");
	
	//parsing infos
	$document = new SimpleXMLElement($feed);

	$xml .= "\t<unreadmails>\n";
	
	//getting unread mails count
	$unread_mails_count = $document->fullcount[0]; 
	$xml .= "\t\t<count>". $unread_mails_count ."</count>\n";

	//getting last 3 unread mails infos
	for ($i = 0; $i < $unread_mails_count && $i < 3; $i++) { 
		$mail = $document->entry[$i];
		//formatting infos -> author : title(...)
		$xml .= "\t\t<mail>". truncate(stripAccents($mail->author[0]->name[0] ." : ". $mail->title[0]), 50) ."</mail>\n";
	}

	$xml .= "\t</unreadmails>\n";
	$xml .= "</response>\n";
}
catch(Exception $e) {
	//setting error message
	$xml = "<response>\n\t<error/>\n</response>\n";
}

//returning infos
echo $xml ;
?>