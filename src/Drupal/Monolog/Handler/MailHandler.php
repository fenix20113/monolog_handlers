<?php

namespace Drupal\Monolog\Handler;

use Monolog\Handler\MailHandler as AbstractMailHandler;
use Monolog\Logger;

/**
 * Created by PhpStorm.
 * User: Yuriy Paliy
 * Date: 12/9/16
 * Time: 5:24 PM
 */
class MailHandler extends AbstractMailHandler
{
  protected $to;
  protected $from;
  protected $subject;

  public function __construct($to, $from, $subject, $level = Logger::DEBUG, $bubble = TRUE) {
    parent::__construct($level, $bubble);
    $this->to = is_array($to) ? $to : [$to];
    $this->from = $from;
    $this->subject = $subject;
  }

  protected function send($content, array $records) {
    $params = array(
      'context' => array(
        'subject' => $this->subject,
        'message' => $content,
      )
    );
    drupal_mail('system', 'action_send_email', $this->to, language_default(), $params, $this->from);
  }
}