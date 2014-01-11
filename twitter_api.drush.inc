<?php
/**
 * @file twitter_api.drush.inc
 */

/**
 * Implements hook_drush_command().
 */
function twitter_api_drush_command() {
  $items = array();

  $items['twitter-api-get'] = array(
    'description' => "Send GET requests to Twitter's API",
    'arguments' => array(
      'resource' => 'Relative path to any resouce documented here: https://dev.twitter.com/docs/api/1.1',
    ),
    'options' => array(
      'callback' => 'Wrap JSON result in a JSONP callback defined here.',
      'format' => 'TODO provide options'
    ),
    'examples' => array(
      'drush twitter-api-get "statuses/user_timeline.json?screen_name=whitehouse&count=3&include_rts=1"' => '',
      'drush tg "statuses/user_timeline.json?screen_name=whitehouse&count=1" --calback=myCallback' => '',
      'drush tg "statuses/user_timeline.json?screen_name=whitehouse&count=1" --format=json' => '',
      'drush tg "statuses/user_timeline.json?screen_name=whitehouse&count=1" --format=pretty' => '',
    ),
    'aliases' => array(tg),
  );

  return $items;
}

/**
 * Implements hook_drush_help().
 */
function twitter_api_drush_help($section) {
  // TODO
}

/**
 *
 */
function drush_twitter_api_twitter_api_get($request) {
  $twitterApi = new TwitterApi();
  $response = $twitterApi->get($request);

  $format = drush_get_option('format');
  $callback = drush_get_option('callback');

  if ($format == 'json' || $callback) {
    // Return response as JSON.
    $response = json_encode($response);
  }
  if ($callback) {
    // Return JSONP.
    $response = $callback . '(' . $response . ')';
  }
  if ($format == 'pretty' || ($format != 'json' && !$callback) ) {
    $response = print_r($response);
  }

  drush_print($response);
}
