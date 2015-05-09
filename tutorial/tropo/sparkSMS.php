<?php
function sendSparkEvent($evtName, $evtData, $evtPrivate = 'true', $evtTtl = 60) {
    $url = 'https://api.spark.io/v1/devices/events';
    
    $fields = array(
        'access_token' => "ACCESS_TOKEN",
        'name' => $evtName,
        'data' => $evtData,
        'private' => $evtPrivate,
        'ttl' => $evtTtl
    );
    $fields_string = http_build_query($fields);

    //open connection
    $ch = curl_init();
    
    //set the url, number of POST vars, POST data
    curl_setopt($ch,CURLOPT_URL, $url);
    curl_setopt($ch,CURLOPT_POST, count($fields));
    curl_setopt($ch,CURLOPT_POSTFIELDS, $fields_string);
    curl_setopt($ch, CURLOPT_HTTPHEADER, array('Content-Type: application/x-www-form-urlencoded'));
    curl_setopt($ch, CURLOPT_RETURNTRANSFER, true);
     
    $output = curl_exec($ch);
     
    if (curl_getinfo($ch, CURLINFO_HTTP_CODE) != '200') {
        return curl_getinfo($ch, CURLINFO_HTTP_CODE) . " - " . $output;
    }
    return $output;
}

$data = array('text' => $currentCall->initialText, 'caller' => $currentCall->callerID);

$response = sendSparkEvent("SMSINC", json_encode($data));
say("Your text '" . $currentCall->initialText . "' was sent to the Spark Cloud. Response " . $response);
?>
