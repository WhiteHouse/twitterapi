<?php

use Guzzle\Http\Client;
use Guzzle\Plugin\Oauth\OauthPlugin;

/**
 * Provides a simple wrapper around Twitter's REST API to make it
 * really easy to use with PHP.
 *
 * Basic interface: 
 *   TwitterApi::get
 *   TODO TwitterApi::post
 *   TODO TwitterApi::put
 *   TODO TwitterApi::delete
 */
class TwitterApi {

  /**
   * Simple wrapper around Twitter REST API for GET requests.
   *
   * Just do this:
   *  $twitterapi = new TwitterApi();
   *  $twitterapi->get($request);
   *
   * @param string $path
   *   Pass any valid get request, documented here
   *   https://dev.twitter.com/docs/api/1.1
   *   E.g. 'statuses/user_timeline.json?screen_name=whitehouse&count=2&include_rts=1'
   *
   * @return array $response
   *   Response from Twitter API, JSON decoded into a PHP array.
   *   Returns false if request fails.
   */
  public function get($request) {
    $client = new Client('https://api.twitter.com/1.1');

    // Get credentials.
    if (!$creds = variable_get('twitter_api_credentials', false)) {
      throw new Exception('Missing required twitter_api_credentials. See twitter_api/README');
    }

    // Use Guzzle's Oauth plugin to take care of authentication.
    $oauth = new OauthPlugin($creds);
    $client->addSubscriber($oauth);

    // Send request.
    $response = $client->get($request)->send();

    // Confirm success or report failure.
    $statusCode = (int) $response->getStatusCode();
    if ($statusCode != 200) {
      $reasonPhrase = $response->getReasonPhrase();
      $message = t('!code: !reason. Request to !request failed.',
        array('!code' => $statusCode, '!reason' => $reasonPhrase));
      watchdog('TwitterApi', $message);
      return FALSE;
    }

    return $response->json();
  }

}
