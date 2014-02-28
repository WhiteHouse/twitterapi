Twitter API
===========

This module includes a simple interface for Twitter's REST API, documented here:
https://dev.twitter.com/docs/api/1.1


Dependencies
------------

  - guzzle
  - composer_autoload


Install / Set-up
----------------

  - Register your app at dev.twitter.com to get OAuth credentials
  - Store your Twitter API creds in settings.php like this:
        ```php
        $conf['twitterapi_credentials'] = array(
          'consumer_key'    => 'xxx',
          'consumer_secret' => 'xxx',
          'token'           => 'xxx',
          'token_secret'    => 'xxx',
        );
        ```
  - Enable the module like this:
        ```bash
        drush en twitterapi
        ```


Usage
-----

  To use this in a module make any GET request documented here,
  https://dev.twitter.com/docs/api/1.1, like this:

    ```php
    $twitterapi = new TwitterApi();
    $response = $twitterapi->get('statuses/user_timeline.json?screen_name=whitehouse&count=3');
    ```


  To make API calls via Drush which can be used to generate static JSON (or JSONP)
  files to be copied up to a CDN:

    ```bash
    drush twitterapi-get 'statuses/user_timeline.json?screen_name=whitehouse&count=3'
    drush tg 'statuses/user_timeline.json?screen_name=whitehouse&count=3'
    drush tg 'statuses/user_timeline.json?screen_name=whitehouse&count=3' --callback=myJSONPCallbackGoesHere
    ```
