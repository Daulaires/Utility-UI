# WinSocketConsole

## Description
 - Recreate Certificate
	- makecert -r -pe -n "CN=Daulaires" -ss MY -sr LocalMachine -a sha256 -sky exchange -sv Daulaires.pvk Daulaires.cer
 - Self Signing Certificate
	- signtool sign /f "Daualaires.pfx" /p RocketBunny$$ /fd sha256 /t "http://timestamp.digicert.com" /v "D:\Projects\Google\python\IOT\MYThing\WinSocketConsole\x64\Release\Daulaires.exe"
