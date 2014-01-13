<?php

/**
 * @file
 * Contains TwitterApi.
 */

use Guzzle\Http\Client;
use Guzzle\Plugin\Oauth\OauthPlugin;

/**
 * Provides a simple wrapper around Twitter's REST API.
 *
 * @todo TwitterApi::post()
 * @todo TwitterApi::put()
 * @todo TwitterApi::delete()
 */
class TwitterApi {

  /**
   * Simple wrapper around Twitter REST API for GET requests.
   *
   * Just do this:
   * @code
   * $twitterapi = new TwitterApi();
   * $twitterapi->get($request);
   * @endcode
   *
   * @param string $request
   *   Pass any valid get request, documented
   *   @link https://dev.twitter.com/docs/api/1.1 here @endlink
   *   . e.g.,
   *   statuses/user_timeline.json?screen_name=whitehouse&count=2&include_rts=1.
   *
   * @return array|false
   *   A response from Twitter API, JSON decoded into a PHP array, or FALSE if
   *   the request fails.
   */
  public function get($request) {
    $client = new Client('https://api.twitter.com/1.1');

    // Get credentials.
    $creds = variable_get('twitterapi_credentials', FALSE);
    if (!$creds) {
      throw new Exception('Missing required twitterapi_credentials variable. See twitterapi/README');
    }

    // Use Guzzle's Oauth plugin to take care of authentication.
    $oauth = new OauthPlugin($creds);
    $client->addSubscriber($oauth);

    // Send request.
    $response = $client->get($request)->send();

    // Confirm success or report failure.
    $status_code = (int) $response->getStatusCode();
    if ($status_code != 200) {
      $reason_phrase = $response->getReasonPhrase();
      $message = t('!code: !reason. Request failed.', array(
        '!code' => $status_code,
        '!reason' => $reason_phrase,
      ));
      watchdog('TwitterApi', $message);
      return FALSE;
    }

    return $response->json();
  }

}
